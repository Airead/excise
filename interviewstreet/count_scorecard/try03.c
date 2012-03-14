#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int muti_for(int deepth, int ori_value, int limit, int *trace, unsigned long *count, int people)
{
    int i;
    int *p;

    for (i = ori_value; i <= limit; i++) {
        trace[deepth-1] = i;
        if (i >= people) {
            break;
        }
        if (deepth > 1) {
            muti_for(deepth - 1, ori_value, limit - i, trace, count, people);
        } else {
/*
            p = trace;
            while (*p != -1) {
                printf("%d,",*p++);
            }
            printf("\n");
*/  
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

    if (argc < 4) {
        fprintf(stderr, "usage: %s <people_num> <sum> <num_x>\n", argv[0]);
        exit(1);
    }

    people = strtol(argv[1], NULL, 10);
    limit = strtol(argv[2], NULL, 10);
    deepth = strtol(argv[3], NULL, 10);

    size = sizeof(int) * (deepth + 1);
    trace = malloc(size);
    if(trace == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    memset(trace, 0, size);
    trace[deepth] = -1;

    count = 0;
    muti_for(deepth, 0, limit, trace, &count, people);
    printf("%lu\n",count);
    free(trace);        
    
    return 0;
}
