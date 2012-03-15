#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int muti_for(int deepth, int ori_value, int limit, int *trace, unsigned long *count, int people)
{
    int i;

    for (i = ori_value; i <= limit; i++) {
        trace[deepth-1] = i;
        if (i >= people) {
            break;
        }
        if (deepth > 1) {
            muti_for(deepth - 1, ori_value, limit - i, trace, count, people);
        } else {
            if (limit - i < people) {
                (*count)++;
            }
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int deepth, limit, people;
    unsigned long count;
    int *trace, size;
    int i, j;

    if (argc < 4) {
        fprintf(stderr, "usage: %s <people_num> <sum> <num_x>\n", argv[0]);
        exit(1);
    }

    people = strtol(argv[1], NULL, 10);
    limit = strtol(argv[2], NULL, 10);
    deepth = strtol(argv[3], NULL, 10);

    for (i = 0; i <= limit; i++) {
        fprintf(stderr, "limit:%2d\t",i);
        for (j = 1; j <= deepth; j++) {
            size = sizeof(int) * (j + 1);
            trace = malloc(size);
            if(trace == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            memset(trace, 0, size);
            trace[j] = -1;

            count = 0;
            muti_for(j, 0, i, trace, &count, people);
            fprintf(stderr, "%10lu  ",count);
            free(trace);        
        }
        printf("\n");
    }
    
    return 0;
}
