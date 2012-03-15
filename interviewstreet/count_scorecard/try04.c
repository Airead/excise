/**
 * @file try04.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/15 13:46:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long T(unsigned long *matrix, int fix_earse, int people, int score, int earse)
{
    unsigned long t[3];

    if (score < 0) {
        return 0;
    }

    if (score == 0 || earse == 0) {
        return matrix[(score * fix_earse) + earse];
    }

    if (matrix[(score * fix_earse) + earse] != 0) {
        return matrix[(score * fix_earse) + earse];
    }


    t[0] = T(matrix, fix_earse, people, score - 1, earse);
    t[1] = T(matrix, fix_earse, people, score, earse -1);
    t[2] = T(matrix, fix_earse, people, score - people, earse -1);

    matrix[(score * fix_earse) + earse] = t[0] + t[1] - t[2];

    return matrix[(score * fix_earse) + earse];
}

unsigned long get_possible_num(int people, int score, int earse)
{
    unsigned ret;
    unsigned long *matrix, size;;
    int i, j;
    
    size = sizeof(unsigned long) * (score + 1) * (earse);
    printf("%d,%d size = %lu\n", score, earse -1, size);
    if ((matrix = malloc(size)) == NULL) {
        fprintf(stderr, "malloc failed\n");
        return -1;
    }

    memset(matrix, 0, size);

    /* initialize T(s,1) */
    for (i = 0; i <= score; i++) {
        if (i < people) {
            matrix[(i * earse)] = 1;
        }
    }
    
    /* initialize T(1,e) */
    for (i = 0; i < earse; i++) {
        matrix[i] = 1;
    }

    for (i = 0; i <= score; i++) {
        for (j = 0; j < earse; j++) {
            printf("%8lu", matrix[(i * earse)+j]);
        }
        printf("\n");
    }
    printf("==================\n");

    ret = T(matrix, earse, people, score, earse - 1);

    for (i = 0; i <= score; i++) {
        printf("limit:%2d\t", i);
        for (j = 0; j < earse; j++) {
            printf("%10lu  ", matrix[(i * earse)+j]);
        }
        printf("\n");
    }
    printf("==================\n");

    free(matrix);
 
   return ret;
}

int main(int argc, char *argv[])
{
    int score, earse, people;
    unsigned long ret;

    if (argc < 4) {
        fprintf(stderr, "usage: %s <people> <score> <earse>\n", argv[0]);
        exit(1);
    }
    
    people = strtol(argv[1], NULL, 10);
    score = strtol(argv[2], NULL, 10);
    earse= strtol(argv[3], NULL, 10);
    
    printf("people:%d, score:%d, earse:%d\n", people, score, earse);

    if (earse > 0) {
        ret = get_possible_num(people, score, earse);
    } else {
        ret = 1;
    }
    printf("%lu\n", ret);
    
    return 0;
}

