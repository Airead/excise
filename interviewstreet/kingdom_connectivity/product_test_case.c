/**
 * @file product_test_case.c
 * @brief rand product Kindom Connectivity test case
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  3月 06 11:08:16 CST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *get_edge_list(int city_num)
{
    int (*edges)[2];
    int i, j, k, size;

    size = sizeof(int) * city_num * city_num;
    if ((edges = malloc(size)) == NULL) {
        fprintf(stderr, "create edge failed\n");
        return NULL;
    }
    memset(edges, 0, size);

    k = 0;
    for (i = 0; i < city_num; i++) {
        for (j = 0; j < city_num; j++) {
            edges[k][0] = i + 1;
            edges[k][1] = j + 1;
            k++;
        }
    }
/*
    for (k = 0; k < edge_num * edge_num; k++) {
        fprintf(stdout, "%d %d\n", edges[k][0], edges[k][1]);
    }
*/
    return (int *)edges;
}

int main(int argc, char *argv[])
{
    int city_num, edge_num, case_num;
    int *num, (*edges)[2];
    int i, j, k, m;

    if (argc < 4) {
        fprintf(stderr, "usage: %s <city_num> <edge_num> <case_num>\n", argv[0]);
        exit(1);
    }
    
    city_num = strtol(argv[1], NULL, 10);
    edge_num = strtol(argv[2], NULL, 10);
    case_num = strtol(argv[3], NULL, 10);

    num = get_edge_list(city_num);
    edges = (int (*)[2])num;
/*
    for (k = 0; k < edge_num * edge_num; k++) {
        fprintf(stdout, "%d->%d\n", edges[k][0], edges[k][1]);
    }
*/
    srand(47);

    for (k = 0; k < case_num; k++) {
        int check_list[city_num * city_num];

        memset(check_list, 0, sizeof(check_list));
        fprintf(stdout, "%d %d\n", city_num, edge_num);
        for (j = 0; j < edge_num; ) {
            i = rand() % (city_num * city_num);
            if (check_list[i] == 0) {
                check_list[i] = 1;
                fprintf(stdout, "%d %d\n", edges[i][0], edges[i][1]);
                j++;
            }
        }
        fprintf(stdout, "===\n");
    }

    return 0;
}
