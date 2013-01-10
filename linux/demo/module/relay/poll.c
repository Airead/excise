/**
 * @file poll.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/06 13:52:34
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <pthread.h>
#include <stdlib.h>

/* max cpu number */
#define NR_CPUS 256

#define BUF_SIZE 10

static int quit;
static int relay_file[NR_CPUS];
static int out_file;
static void signal_handler(int sig)
{
    fprintf(stdout, "Caught signal %d.\n", sig);
    quit = 1;
}

static int install_signal(void)
{
    struct sigaction act, oact;

    memset(&act, 0, sizeof(act));

    act.sa_handler = signal_handler;
    //int sigemptyset(sigset_t *set);
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    if (sigaction(SIGINT, &act, &oact) < 0) {
        fprintf(stderr, "Install new signal handler for SIGINT failed: %s\n", strerror(errno));
    }

    if (sigaction(SIGTERM, &act, &oact) < 0) {
        fprintf(stderr, "Install new signal handler for SIGTERM failed: %s\n", strerror(errno));
    }

    if (sigaction(SIGQUIT, &act, &oact) < 0) {
        fprintf(stderr, "Install new signal handler for SIGQUIT failed: %s\n", strerror(errno));
    }

    return 0;
}

static int open_input_files(int ncpus, char *file)
{
	int i;
    char tmp[4096];

	for (i = 0; i < ncpus; i++) {
        snprintf(tmp, sizeof(tmp), "%s%d", file, i);
        relay_file[i] = open(tmp, O_RDONLY | O_NONBLOCK);
        if (relay_file[i] < 0) {
            fprintf(stderr, "Couldn't open relay file %s: errcode = %s\n",
                   tmp, strerror(errno));
            return -1;
        }
	}

	return 0;
}

static int open_output_file(char *file)
{
    out_file = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (out_file < 0) {
        fprintf(stderr, "Couldn't open relay file %s: errcode = %s\n",
                file, strerror(errno));
        return -1;
    }

    return 0;
}

static int poll_start(int ncpus)
{
    char buf[BUF_SIZE];
	int ret;
    int cpu;
	unsigned seq;
	struct pollfd pollfd[NR_CPUS];

    /* reset fd for poll */
    for (cpu = 0; cpu < ncpus; cpu++) {
        pollfd[cpu].fd = relay_file[cpu];
        pollfd[cpu].events = POLLIN;
    }

    ret = poll(pollfd, ncpus, 1000);
    if (ret < 0) {
        if (errno != EINTR) {
            fprintf(stderr, "poll error: %s\n", strerror(errno));
            return -1;
        }
        fprintf(stdout, "poll warning: %s\n", strerror(errno));
    }

    /* start to read and write */
    for (cpu = 0; cpu < ncpus; cpu++) {
        if (pollfd[cpu].revents & POLLIN) {
            while ((ret = read(relay_file[cpu], buf, BUF_SIZE))) {
                if (ret < 0) {
                    if (errno == EAGAIN)
                        continue;
                    fprintf(stderr, "read error: %s\n", strerror(errno));
                    break;
                }
                fprintf(stdout, "read %d bytes\n", ret);
                write(out_file, buf, ret);
            }
            /* ret = read(relay_file[cpu], buf, BUF_SIZE); */
            /* if (ret < 0) { */
            /*     if (errno == EAGAIN) */
            /*         continue; */
            /*     fprintf(stderr, "read error: %s\n", strerror(errno)); */
            /*     break; */
            /* } */
            /* fprintf(stdout, "read %d bytes\n", ret); */
            /* write(out_file, buf, ret); */
        } else if (pollfd[cpu].revents & POLLERR) {
            fprintf(stdout, "poll error\n");
            return -1;
        } else if (pollfd[cpu].revents & POLLHUP) {
            fprintf(stdout, "poll hup\n");
            return -1;
        } else if (pollfd[cpu].revents & POLLNVAL) {
            fprintf(stdout, "poll nval\n");
            return -1;
        }
    }

    if (ret < 0) {
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    int ncpus;

    install_signal();

	ncpus = sysconf(_SC_NPROCESSORS_ONLN);

    if (open_input_files(ncpus, "/sys/kernel/debug/relay/relay") < 0) {
        goto open_input_files_failed;
    }

    if (open_output_file("relay.log") < 0) {
        goto open_output_file_failed;
    }

    for (;;) {
        if (quit) {
            break;
        }
        if (poll_start(ncpus) < 0) {
            fprintf(stderr, "poll error!\n");
            break;
        }
    }

    return 0;

open_output_file_failed:
open_input_files_failed:
    for (i = 0; i < ncpus; i++) {
        close(relay_file[i]);
    }
    exit(1);
}
