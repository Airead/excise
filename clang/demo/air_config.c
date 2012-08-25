/**
 * @file air_config.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/25 16:02:05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define CONFIG_KEY_SIZE 64
#define CONFIG_VALUE_SIZE 128
#define CONFIG_ERROR_SIZE 256

/**
 * @brief state overview
 *
 * APSOK:
 *     parse configure file ok. when reaching file end, and (kp == key && vp == value) (key value is complete) APSOK will return.
 * APSSTART:
 *     core state transmit routing. special char: '
 * APSCOMMENT:
 *     skip all char until receive '\n'
 * APSSPACE:
 *     skip all ' ' and '\t'.
 * APSSTRING:
 *     store all char until receive '"'
 * APSKSTART:
 *     speacial char ' ', '\t', ';' stand for key end;
 * APSVSTART:
 *     ' ', '\t', ',', ';' stand for value end; '"' stands for string start;
 * APSVASTART:
 *     value array start
 * APSVAEND:
 *     one value array is ready to add
 * APSKVFIN:
 *     one key-value pair is ready to add
 * APSEEOF:
 *     unexpected file end, the key-value pair is not complete;
 * APSERROR:
 *     some unkonwn error;
 * APSESEMMI:
 *     unexcept semmicolon error
 * APSENEEDCOMMA:
 *     except comma error
 * APSECOMMA:
 *     unexcept comma error
 */

enum air_parse_state {
    APSOK,
    APSSTART,                   /* AIR PARSE STATE START */
    APSCOMMENT,
    APSSPACE,
    APSSTRING,
    APSKSTART,
    APSVSTART,
    APSVASTART,                 /* VALUE ARRAY START */
    APSVAEND,
    APSKVFIN,                   /* KEY VALUE FINISH */
    APSEEOF,
    APSERROR,
    APSESEMMI,                  /* unexpect semicolon*/
    APSENEEDCOMMA,
    APSECOMMA,                 /* unexpect comma */
};
enum air_value_type {
    AVTINT,                     /* AIR VALUE INT */
    AVTUINT,
    AVTBOOL,
    AVTSTR,
};

struct air_config_t {
    struct air_config_t *next;
    char *key;
    void *value;
    int type;
    int isarray;                /* 1 for array, 0 for noarray */
};

char error_info[CONFIG_ERROR_SIZE];

void air_config_destroy(struct air_config_t *ach)
{
    
}

int air_config_get_state(int ch, int aps)
{
    switch(aps) {
    case APSSTART:
        if (ch == ' ' || ch == '\t') {
            return APSSPACE;
        }
    default:
        fprintf(stderr, "config handler error: never reach here\n");
    }

    return APSERROR;
}

int air_config_add(struct air_config_t *ach, char *key, char *value)
{
    fprintf(stdout, "add %s: %s\n", key, value);
    return 0;
}

/* aps stands for air_parse_state */
int air_config_handler(struct air_config_t *ach, FILE *in, int aps, char *error)
{
    char ch;
    char key[CONFIG_KEY_SIZE], *kp;
    char value[CONFIG_VALUE_SIZE], *vp;
    int ln;                     /* line number */
    int used;
    int isarray;                /* 1 for array, 0 for noarray */

    isarray = 0;
    ln = 1;
    kp = key;
    vp = value;
    used = 0;
    memset(error, 0, CONFIG_ERROR_SIZE);
    used += snprintf(error, CONFIG_ERROR_SIZE, "line [%d], ", ln);

    while ((ch = fgetc(in)) != EOF) {
        if (used < CONFIG_ERROR_SIZE - 1) {
            error[used++] = ch;
        }
    goon:
        switch(aps) {
        case APSSTART:
            switch (ch) {
            case '\n':
                ln++;
                used = 0;
                memset(error, 0, CONFIG_ERROR_SIZE);
                used += snprintf(error, CONFIG_ERROR_SIZE, "line [%d], ", ln);
                break;
            case ' ':
            case '\t':
                aps = APSSPACE;
                break;
            case '#':
                aps = APSCOMMENT;
                break;
            case '{':
                isarray = 1;
                aps = APSVASTART;
                break;
            case '}':
                isarray = 0;
                if (value != vp) {
                    aps = APSENEEDCOMMA;
                    goto failed;
                }
                kp = key;
                break;
            case ',':
                if (isarray != 1) {
                    aps = APSECOMMA;
                    goto failed;
                }
                *vp = '\0';
                if (key != kp && value != vp) {
                    vp = value;
                    aps = APSVAEND;
                } else {
                    aps = APSECOMMA;
                    goto failed;
                }
                break;
            case ';':
                if (key != kp && value != vp) {
                    kp = key;
                    vp = value;
                    aps = APSKVFIN;
                } else if (key == kp && value == vp){
                    /* goto next char */
                } else {
                    aps = APSESEMMI;
                    goto failed;
                }
                break;
            default:
                if (key == kp) {
                    aps = APSKSTART;
                } else if (value == vp) {
                    aps = APSVSTART;
                } else {
                    aps = APSERROR;
                    goto failed;
                }
                goto goon;
                break;
            }
            break;
        case APSSPACE:
            switch (ch) {
            case ' ':
            case '\t':
                break;
            default:
                aps = APSSTART; 
                goto goon;
                break;
            }
            break;
        case APSCOMMENT:
            switch (ch) {
            case '\n':
                aps = APSSTART;
                goto goon;
                break;
            default:
                break;
            }
            break;
        case APSKSTART:
            switch (ch) {
            case ' ':
            case '\t':
                *kp = '\0';
                aps = APSSPACE;
                goto goon;
                break;
            case ';':
                aps = APSSTART;
                *kp = '\0';
                goto goon;
            default:
                *kp++ = ch;
                break;
            }
            break;
        case APSVSTART:
            switch (ch) {
            case ' ':
            case '\t':
                *vp = '\0';
                aps = APSSPACE;
                goto goon;
                break;
            case ';':
                aps = APSSTART;
                *vp = '\0';
                goto goon;
            case '"':
                aps = APSSTRING;
                break;
            case '}':
            case ',':
                aps = APSSTART;
                goto goon;
                break;
            default:
                *vp++ = ch;
                break;
            }
            break;
        case APSSTRING:         /* only can enter from APSVSTART */
            switch (ch) {
            case '"':
                aps = APSVSTART; /* return to parse value routing */
                break;
            default:
                *vp++ = ch;
            }
            break;
        case APSVASTART:
            switch (ch) {
            case ' ':
            case '\t':
                aps = APSSPACE;
                break;
            case '\n':
                aps = APSSTART;
                goto goon;
                break;
            default:
                aps = APSVSTART;
                goto goon;
            }
            break;
        case APSVAEND:
            air_config_add(ach, key, value);
            aps = APSVASTART;
            goto goon;          /* for line number */
            break;
        case APSKVFIN: 
            air_config_add(ach, key, value);
            aps = APSSTART;
            goto goon;          /* for line number */
            break;
        default:
            fprintf(stderr, "config handler error: never reach here\n");
            break;
        }
    }

    if (kp == key && vp == value) {
        aps = APSOK;
    } else {
        aps = APSEEOF;
    }

failed:
    return aps;
}

struct air_config_t *air_config_parse(char *file, char **error)
{
    FILE *in;
    struct air_config_t *ach;    /* air config header */
//    int ch[2] = {0,0};                  /* ch[0] current char, ch[1] save char */
    int ret;
//    enum air_parse_state aps, newaps;
    
    in = fopen(file, "r");
    if (in == NULL) {
        fprintf(stderr, "open %s failed: %s\n", file, strerror(errno));
        goto failed;
    }

    ach = malloc(sizeof(struct air_config_t));
    if (ach == NULL) {
        fprintf(stderr, "malloc config header failed: %s\n", strerror(errno));
        goto failed;
    }
    memset(ach, 0, sizeof(struct air_config_t));

    ret = air_config_handler(ach, in, APSSTART, error_info);
    switch (ret) {
    case APSOK:
        break;
    case APSERROR:
        fprintf(stderr, "unknown error\n");
        goto failed;
        break;
    case APSESEMMI:
        fprintf(stderr, "unexpect semmicolon\n");
        goto failed;
        break;
    case APSECOMMA:
        fprintf(stderr, "unexpect comma\n");
        goto failed;
        break;
    case APSEEOF:
        fprintf(stderr, "unexpect file end\n");
        goto failed;
        break;
    case APSENEEDCOMMA:
        fprintf(stderr, "expect comma\n");
        goto failed;
        break;
    default:
        fprintf(stderr, "never reach here, state %d\n", ret);
        goto failed;
        break;
    }
    
    *error = NULL;
    return ach;
failed:
    *error = error_info;
    if (in) {
        fclose(in);
    }
    
    if (ach) {
        air_config_destroy(ach);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    char *file;
    char *error;
    struct air_config_t *configh; /* config handler */

    file = "example.conf";
    configh = air_config_parse(file, &error);
    if (configh == NULL) {
        fprintf(stderr, "air_conifg_parse failed: %s\n", error);
        exit(1); 
    }
    
    return 0;
}

