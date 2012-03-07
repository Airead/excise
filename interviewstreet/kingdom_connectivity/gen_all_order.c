/**
 * @file gen_all_order.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  3月 06 11:24:47 CST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, j, n;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <num>\n", argv[0]);
        exit(1);
    }

    n = strtol(argv[1], NULL, 10);
    
    fprintf(stdout, "%d\n", n * n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(stdout, "%d %d\n", i + 1, j + 1);
        }
    }
    
    return 0;
}
