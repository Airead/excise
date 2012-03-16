/**
 * @file count_scorecard.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/07 16:24:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_

#ifdef _DEBUG_
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

struct test_case {
    int num;
    int *s_list;
};

int get_case(struct test_case *cases)
{
    int i;
    int size;

    scanf("%d", &cases->num);

    size = sizeof(int) * cases->num;
    if ((cases->s_list = malloc(size)) == NULL) {
        fprintf(stderr, "malloc failed\n");
        return -1;
    }
    memset(cases->s_list, 0, size);

    for (i = 0; i < cases->num; i++) {
        scanf("%d", cases->s_list + i);
    }

    return 0;
}

struct test_case *get_cases(int *num)
{
    int i;
    int size;
    struct test_case *cases;

    scanf("%d", num);
    
    size = sizeof(struct test_case) * *num;
    if ((cases = malloc(size)) == NULL) {
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }
    memset(cases, 0, size);

    for (i = 0; i < *num; i++) {
        if (get_case(&cases[i]) < 0) {
            return NULL;
        }
    }
    
    return cases;
}

int get_known_sum(struct test_case *c, int *known_num)
{
    int count, sum;
    int i;
    
    count = 0;
    sum = 0;
    for (i = 0; i < c->num; i++) {
        if (c->s_list[i] >= 0) {
            count++;
            sum += c->s_list[i];
        }
    }

    *known_num = count;
    
    return sum;
}

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

    return matrix[cor];
}

unsigned long solve_with_matrix(int people, int score, int earse)
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
#ifdef _DEBUG_
    for (i = 0; i <= score; i++) {
        for (j = 0; j < earse; j++) {
            printf("%8lu", matrix[(i * earse)+j]);
        }
        printf("\n");
    }
    printf("==================\n");
#endif

    ret = T(matrix, score, earse, people, score, earse - 1);

#ifdef _DEBUG_
    for (i = 0; i <= score; i++) {
        printf("limit:%2d\t", i);
        for (j = 0; j < earse; j++) {
            printf("%10lu  ", matrix[(i * earse)+j]);
        }
        printf("\n");
    }
    printf("==================\n");
#endif

    free(matrix);
 
   return ret;
}

/**
 * N(N-1)/2 = x1 + x2 + ... + xi + xj + ...
 * ==> N(N-1)/2 - (x1 + x2 + ...) = xi + xj + ...
 * ==> total_socre - known_sum = xi + xj + ...
 * ==> unknown_sum = xi + xj + ...
 */
unsigned long get_possible_num(struct test_case *c)
{
    int total_socre, known_sum, unknown_sum;
    int known_num, unknown_num;
    unsigned long pos_num;

    pos_num = 0;

    total_socre = (c->num * (c->num -1)) / 2;
    known_sum = get_known_sum(c, &known_num);
    if (total_socre < known_sum) {
        return 0;
    }

    unknown_sum = total_socre - known_sum;
    unknown_num = c->num - known_num;

    if (unknown_num > 0) {
        pos_num = solve_with_matrix(c->num, unknown_sum, unknown_num);
    } else {
        pos_num = 1;
    }

    return pos_num;
}

int debug_cases(struct test_case *cases, int case_num)
{
    int i, j;

    for (i = 0; i < case_num; i++) {
        fprintf(stdout, "%4d | ", cases[i].num);
        for (j = 0; j < cases[i].num; j++) {
            fprintf(stdout, "%d, ", cases[i].s_list[j]);
        }
        fprintf(stdout, "\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    int case_num;
    unsigned long pos_num;
    struct test_case *cases;

    if ((cases = get_cases(&case_num)) == NULL) {
        exit(1);
    }
    
//    debug_cases(cases, case_num);

    for (i = 0; i < case_num; i++) {
        pos_num = get_possible_num(&cases[i]);
        fprintf(stdout, "%lu\n", pos_num);
    }
    
    return 0;
}


