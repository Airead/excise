#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int s);

int main(int argc, char **argv)
{
  signal(SIGALRM, signal_handler);

  sigset_t s, o;

  //int sigemptyset(sigset_t *set);
  sigemptyset(&s);

  //int sigaddset(sigset_t *set, int signum);
  sigaddset(&s, SIGALRM);

  //int sigprocmask(int how, const sigset_t * set, sigset_t * oldset);
  if (sigprocmask(SIG_BLOCK, &s, &o) < 0)
  {
    fprintf(stderr, "Change signal mask failed: %s\n", strerror(errno));
    exit(1);
  }

  alarm(5);

  //sleep(10);

  //int sigdelset(sigset_t *set, int signum);
  sigdelset(&o, SIGALRM);

  //int sigsuspend(const sigset_t * mask);
  sigsuspend(&o);

  fprintf(stdout, "Can I go here?\n");

  return 0;
}

void signal_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);
}
