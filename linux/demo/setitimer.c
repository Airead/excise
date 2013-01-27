/**
 * @file setitimer.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/14 10:04:10
 */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#if 0
int getitimer(int which, struct itimerval *curr_value);
int setitimer(int which, const struct itimerval *new_value,
              struct itimerval *old_value);
#endif

static int is_print;

static void signal_handler(int sig)
{
    is_print = 1;
}


int main(int argc, char *argv[])
{
    struct sigaction act, oact;
    struct itimerval tick;

    memset(&act, 0, sizeof(act));

    act.sa_handler = signal_handler;
    //int sigemptyset(sigset_t *set);
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    if (sigaction(SIGALRM, &act, &oact) < 0) {
        fprintf(stderr, "Install new signal handler for SIGINT failed: %s\n", strerror(errno));
    }

    memset(&tick, 0, sizeof(tick));
    tick.it_value.tv_sec = 1;
    tick.it_interval.tv_sec = 1;
    if (setitimer(ITIMER_REAL, &tick, NULL) < 0) {
        fprintf(stderr, "setitimer failed: %s\n", strerror(errno));
        exit(1);
    }
    
    while (1) {
        sleep(2);
        if (is_print == 1) {
            fprintf(stdout, ".\n");
            is_print = 0;
        }
    }

    return 0;
}
