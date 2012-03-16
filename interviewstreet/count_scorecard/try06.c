/**
 * @file try04.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/15 13:46:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long T(unsigned long *matrix, int fix_score, int fix_earse, int people, int score, int earse)
{
    unsigned long t[3];
    int cor, x_cor;             /* symmetrical about the x-axis */
    int line;

    if (score < 0) {
        return 0;
    }

    if (score == 0 || earse == 0) {
        return matrix[(score * fix_earse) + earse];
    }

    if (matrix[(score * fix_earse) + earse] != 0) {
        return matrix[(score * fix_earse) + earse];
    }

    t[0] = T(matrix, fix_score, fix_earse, people, score - 1, earse);
    t[1] = T(matrix, fix_score, fix_earse, people, score, earse -1);
    t[2] = T(matrix, fix_score, fix_earse, people, score - people, earse -1);

    cor = score * fix_earse + earse;
    matrix[cor] = (t[0] + t[1] - t[2]) % 1000000007;

    /*
     * (people - 1) * earse - score > (people-1) * earse / 2
     * 2 * (people-1) * earse - 2 * i > (people-1) * earse / 2
     * (p-1)*e > 2*i
     */
    if ((people - 1) * (earse + 1) > 2 * score) {
        line = (people - 1) * (earse + 1) - score;
        if (line <= fix_score) {
            x_cor = line * fix_earse + earse;
            matrix[x_cor] = matrix[cor];
        }
    }

//    printf("==%d,%d,%lu\n", score, earse, matrix[cor]);

    return matrix[cor];
}

unsigned long get_possible_num(int people, int score, int earse)
{
    unsigned ret;
    unsigned long *matrix, size;;
    int i, j;
    
    size = sizeof(unsigned long) * (score + 1) * (earse);
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

    ret = T(matrix, score, earse, people, score, earse - 1);

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
    
    if (earse > 0) {
        ret = get_possible_num(people, score, earse);
    } else {
        ret = 1;
    }
    printf("%lu\n", ret);
    
    return 0;
}

