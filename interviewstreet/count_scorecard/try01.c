/**
 * @file try01.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/13 18:27:23
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum;
    int i, j, k, s, count;

    if (argc < 3) {
        fprintf(stderr, "usage: %s <sum> <num_x>\n", argv[0]);
        exit(1);
    }
    
    sum = strtol(argv[1], NULL, 10);

    count = 0;
    for (i = 0; i <= sum; i++) {
        for(j = 0; j <= sum; j++) {
            for(k = 0; k <= sum; k++) {
                for(s = 0; s <= sum; s++) {
                    if (i + j + k + s == sum) {
                        count++;
                        fprintf(stdout, "[%d] (%d,%d,%d,%d)\n", count, i, j, k, s);
                    }
                }
            }
        }
    }



	return 0;
}

