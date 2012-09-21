/**
 * @file sched_setaffinity.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/13 11:31:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#define __USE_GNU
#include <sched.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    cpu_set_t mask;
    int cpunum;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <cpunum>\n", argv[0]);
        exit(1);
    }
    cpunum = strtol(argv[1], NULL, 10);
    
    CPU_ZERO(&mask);
    CPU_SET(cpunum, &mask);
    fprintf(stdout, "pid %u run in cpu%d\n", getpid(), cpunum);

    //int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        printf("warning: could not set CPU affinity, continuing...\n");
    }
    
    for(;;);

    return 0;
}



