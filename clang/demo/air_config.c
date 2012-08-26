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
    APSEDUP,                   /* duplicate */
};
enum air_value_type {
    AVTINT,                     /* AIR VALUE INT */
    AVTUINT,
    AVTBOOL,
    AVTSTR,
};

struct air_config_value {
    struct air_config_value *next;
    char *value;
};

struct air_config_t {
    struct air_config_t *next;
    char *key;
    void *value;
    int type;
    int array;                /* 1 for array, 0 for noarray */
    int num;
};

char error_info[CONFIG_ERROR_SIZE];

#define config_valueh(key) ((struct air_config_value *)(key->value))

void air_config_destroy_key(struct air_config_t *key)
{
    struct air_config_value *acvp, *wf;

    if (key->key) free(key->key);
    
    if (key->array == 0) {
        if (key->value) free(key->value);
    } else {
        if (key->value) {
            acvp = config_valueh(key)->next;
            while (acvp != NULL) {
                wf = acvp;
                acvp = acvp->next;
                free(wf->value);
                free(wf);
            }
            free(key->value);
        }
    }

    free(key);
}

void air_config_destroy(struct air_config_t *ach)
{
    struct air_config_t *acp, *wd; /* will free */

    fprintf(stdout, "destory list:\n");
    acp = ach->next;
    while (acp != NULL) {
        wd = acp;
        acp = acp->next;
        air_config_destroy_key(wd);
    }

    free(ach);
}

int air_config_append(struct air_config_t *ach, struct air_config_t *node)
{
    struct air_config_t *acp;

    ach->num++;

    acp = ach;
    while (acp->next != NULL) {
        acp = acp->next;
    }
    
    node->next = acp->next;
    acp->next = node;

    return 0;
}

int air_config_append_value(struct air_config_t *key, char *value)
{
    struct air_config_value *tmp;
    struct air_config_value *acvp;

    key->num++;

    tmp = malloc(sizeof(struct air_config_value));
    if (tmp == NULL) {
        fprintf(stderr, "malloc value failed: %s\n", strerror(errno));
        goto failed;
    }
    memset(tmp, 0, sizeof(struct air_config_value));
    
    acvp = config_valueh(key);
    while (acvp->next != NULL) {
        acvp = acvp->next;
    }

    tmp->value = strdup(value);
    
    tmp->next = acvp->next;
    acvp->next = tmp;
    
    return 0;
failed:
    return -1;
}

int air_config_catch(struct air_config_t *ach, char *key, char *value, int array)
{
    struct air_config_t *tmp;
    struct air_config_t *acp;   /* air config pointer */

    fprintf(stdout, "get %s: %s\n", key, value);
    acp = ach->next;
    while (acp != NULL) {
        if (strcmp(key, acp->key) == 0) {
            break;
        }
        acp = acp->next;
    }

    if (acp == NULL) {
        if (array == 0) {
            tmp = malloc(sizeof(struct air_config_t));
            if (tmp == NULL) {
                fprintf(stderr, "config add malloc failed: %s\n", strerror(errno));
                goto failed;
            }
            memset(tmp, 0, sizeof(struct air_config_t));

            tmp->array = array;
            tmp->key = strdup(key);
            tmp->value = strdup(value);
            tmp->num++;
            air_config_append(ach, tmp);
        } else {                /* array == 1 */
            tmp = malloc(sizeof(struct air_config_t));
            if (tmp == NULL) {
                fprintf(stderr, "config add malloc failed: %s\n", strerror(errno));
                goto failed;
            }
            memset(tmp, 0, sizeof(struct air_config_t));

            tmp->array = array;
            tmp->key = strdup(key);
            tmp->value = malloc(sizeof(struct air_config_value));
            if (tmp ->value == NULL) {
                fprintf(stderr, "config_value add malloc failed: %s\n", strerror(errno));
                goto failed;
            }
            memset(tmp->value, 0, sizeof(struct air_config_value));
            air_config_append(ach, tmp);
            air_config_append_value(tmp, value);
        }
    } else if (array == 0) {    /* array == 0 && acp != NULL */
        goto dup;
    } else {                    /* array == 1 && acp != NULL */
        air_config_append_value(acp, value);
    }

    return APSOK;
dup:
    return APSEDUP;
failed:
    if (tmp) free(tmp);
    if (tmp->key) free(tmp->key);
    if (tmp->value) free(tmp->value);
    return APSERROR;
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
    int ret;

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
            ret = air_config_catch(ach, key, value, isarray);
            if (ret == APSEDUP) {
                aps = APSEDUP;
                goto failed;
            }
            aps = APSVASTART;
            goto goon;          /* for line number */
            break;
        case APSKVFIN: 
            ret = air_config_catch(ach, key, value, isarray);
            if (ret == APSEDUP) {
                aps = APSEDUP;
                goto failed;
            }
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
    case APSEDUP:
        fprintf(stderr, "duplicate value not in array\n");
        goto failed;
        break;
    default:
        fprintf(stderr, "never reach here, state %d\n", ret);
        goto failed;
        break;
    }

    fclose(in);
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

void air_config_show_list(struct air_config_t *ach)
{
    struct air_config_t *acp;
    struct air_config_value *acvp;

    fprintf(stdout, "config list:\n");
    acp = ach->next;
    while (acp != NULL) {
        if (acp->array == 0) {
            fprintf(stdout, "%s: %s\n", acp->key, (char *)acp->value);
        } else {
            fprintf(stdout, "%s:\n", acp->key);
            acvp = config_valueh(acp)->next;
            while (acvp != NULL) {
                fprintf(stdout, "    %s\n", acvp->value);
                acvp = acvp->next;
            }
        }
        acp = acp->next;
    }
}

/* just get (struct air_config_t) */
int air_config_get(struct air_config_t *ach, char *key, struct air_config_t **result)
{
    struct air_config_t *acp;

    acp = ach->next;
    while (acp != NULL) {
        if (strcmp(acp->key, key) == 0) {
            break;
        }
        acp = acp->next;
    }
    
    *result = acp;

    return 0;
}

int air_config_get_string(struct air_config_t *ach, char *key, char **result)
{
    struct air_config_t *acp;

    *result = NULL;
    air_config_get(ach, key, &acp);
    if (acp == NULL) {
        fprintf(stderr, "no such key: %s\n", key);
        goto failed;
    }

    if (acp->array == 1) {
        fprintf(stderr, "the value of [%s] is array!\n", key);
        goto failed;
    }

    *result = acp->value;

    return 0;
failed:
    return -1;
}

int air_config_get_array(struct air_config_t *ach, char *key, struct air_config_value **result)
{
    struct air_config_t *acp;

    if (air_config_get(ach, key, &acp) < 0) {
        fprintf(stderr, "no such key: %s\n", key);
        return -1;
    }
    
    if (acp->array == 0) {
        fprintf(stderr, "the value of [%s] is not array!\n", key);
        return -1;
    }

    *result = config_valueh(acp)->next;
    return 0;
}

int air_config_get_int(struct air_config_t *ach, char *key, int *result)
{
    char *str;
    
    if (air_config_get_string(ach, key, &str) < 0) {
        return -1;
    }

    *result = strtol(str, NULL, 10);

    return 0;
}

int main(int argc, char *argv[])
{
    char *file;
    char *error;
    char *value;
    char *key;
    struct air_config_t *configh; /* config handler */
    struct air_config_value *acvp;
    int num_int;

    file = "example.conf";
    configh = air_config_parse(file, &error);
    if (configh == NULL) {
        fprintf(stderr, "air_conifg_parse failed: %s\n", error);
        exit(1); 
    }

    air_config_show_list(configh);

    fprintf(stdout, "=================================\n");

    key = "int";
    air_config_get_int(configh, key, &num_int);
    fprintf(stdout, "search %s, found %s: %d\n", key, key, num_int);

    key = "uint";
    air_config_get_string(configh, key, &value);
    fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");
 
    key = "unex";
    air_config_get_string(configh, key, &value);
    fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");

    key = "string_array";
    air_config_get_array(configh, key, &acvp);
    while (acvp != NULL) {
        value = acvp->value;
        fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");
        acvp = acvp->next;
    }

    air_config_destroy(configh);

    return 0;
}

