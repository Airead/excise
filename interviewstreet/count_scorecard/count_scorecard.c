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

/**
 * @brief multiple for
 * @param limit : unknown_sum
 * @param cy_num : unknown_num
 * @param pos_num : possible num
 * @return 0
 */
int get_possible_num_for(int limit, int cy_num, int p_num, int *pos_num)
{
    int i;

    for (i = 0; i <= limit; i++) {
        DBG("limit: %d, i: %d\n", limit, i);
        if (i == p_num) {
            break;
        }
/*
        if (limit - i == 0) {
            DBG("++\n");
            (*pos_num)++;
            break;
        }
*/  
      if (cy_num - 1 > 0) {
            get_possible_num_for(limit - i, cy_num - 1, p_num, pos_num);
        } else {
            if (limit < p_num) {
                (*pos_num)++;
            }
            break;
        }
    }

    return 0;
}

/**
 * N(N-1)/2 = x1 + x2 + ... + xi + xj + ...
 * ==> N(N-1)/2 - (x1 + x2 + ...) = xi + xj + ...
 * ==> total_socre - known_sum = xi + xj + ...
 * ==> unknown_sum = xi + xj + ...
 */
int get_possible_num(struct test_case *c)
{
    int total_socre, known_sum, unknown_sum;
    int known_num, unknown_num;
    int pos_num;

    pos_num = 0;

    total_socre = (c->num * (c->num -1)) / 2;
    known_sum = get_known_sum(c, &known_num);
    unknown_sum = total_socre - known_sum;
    unknown_num = c->num - known_num;

    get_possible_num_for(unknown_sum, unknown_num, c->num, &pos_num);

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
    int case_num, pos_num;
    struct test_case *cases;

    if ((cases = get_cases(&case_num)) == NULL) {
        exit(1);
    }
    
//    debug_cases(cases, case_num);

    for (i = 0; i < case_num; i++) {
        pos_num = get_possible_num(&cases[i]);
        fprintf(stdout, "%d\n", pos_num);
    }
    
    return 0;
}


