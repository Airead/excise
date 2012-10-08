/**
 * @file strbuf.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/08 14:21:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strcb {
    char *address;  /* start of memory */
    int size;   /* maximum number of buffer */
    int start;  /* pointer of the oldest string */
    int end;    /* pointer of new string to write */
    int count;
};

int strcb_init(struct strcb *scb, int size)
{
    memset(scb, 0, sizeof(struct strcb));
    
    scb->address = malloc(size);
    if (scb->address == NULL) {
        return -1;
    }
    
    scb->size = size;
    scb->start = 0;
    scb->end = 0;
    scb->count = 0;

    return -1;
}

int strcb_free(struct strcb *scb)
{

    if (scb->address)
        free(scb->address);

    return 0;
}

int strcb_write(struct strcb *scb, char *buf, int len)
{
    if (scb->end > scb->start) {
        if (scb->size - scb->end < len + 1) { /* spare buffer in the rear is not enough */
            if (scb->start  < len + 1) {         /* spare buffer in the head is not enough too */
                /* drop this string */
                goto drop;
            }

            /* store string at address */
            scb->address[scb->end] = -1;
            memcpy(scb->address, buf, len);
            scb->address[len] = '\0';
            scb->end = len + 1;
            goto out;
        }
    } else if (scb->start == scb->end && scb->count != 0) { /* buffer full */
        goto drop;
    } else {
        if (scb->start == scb->end && scb->count == 0) { /* buffer empty */
            if (scb->size - scb->end < len + 1) { /* spare buffer in the rear is not enough */
                scb->address[scb->end] = -1;
                memcpy(scb->address, buf, len);
                scb->address[len] = '\0';
                scb->end = len + 1;
                goto out;
            }
            goto store;
        }
        if (scb->start - scb->end < len + 1) { /* spare buffer in the middle is not enough */
            goto drop;
        }
    }
store:
    /* store string at end */
    memcpy(scb->address + scb->end, buf, len);
    scb->address[scb->end + len] = '\0';
    scb->end = scb->end + len + 1;
    
out:
    scb->count += len + 1;
    return len + 1;

drop:
    return -1;
}

int strcb_read(struct strcb *scb, char **buf, int *len)
{
    if (scb->start == scb->end && scb->count == 0) { /* empty */
        return 0;
    }

    if (scb->address[scb->start] == -1) {
        scb->start = 0;
    }
    
    *buf = scb->address + scb->start;
    *len = 0;
    while (scb->address[scb->start + *len] != '\0') {
        (*len)++;
    }
    
    scb->start += *len + 1;
    scb->count -= *len + 1;

    return *len;
}

int main(int argc, char *argv[])
{
    struct strcb scb;
    int i;
    char *res;
    int len;
    char *str[] = {
        "hello A",
        "happy happy B",
        "tony tony C",
        "ABCDefghijklmnopqrst"
    };

    strcb_init(&scb, 63);

    for (i = 0; i < 10; i++) {
        char *s = str[i % 4];
        if (strcb_write(&scb, s, strlen(s)) < 0) {
            fprintf(stderr, "[%d] drop %s, len: %lu\n", i, s, strlen(s) + 1);
        }
    }

    while (strcb_read(&scb, &res, &len) > 0) {
        fprintf(stdout, "%s, len: %d\n", res, len + 1);
    }

    fprintf(stdout, "=================================\n");

    for (i = 0; i < 10; i++) {
        char *s = str[i % 4];
        if (strcb_write(&scb, s, strlen(s)) < 0) {
            fprintf(stderr, "[%d] drop %s, len: %lu\n", i, s, strlen(s) + 1);
        }
    }

    while (strcb_read(&scb, &res, &len) > 0) {
        fprintf(stdout, "%s, len: %d\n", res, len + 1);
    }

    strcb_free(&scb);
    
    return 0;
}


