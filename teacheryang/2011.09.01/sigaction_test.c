#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig);

int main(int argc, char **argv)
{
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    union
    {
      __sighandler_t sa_handler;
      void (*sa_sigaction) (int, siginfo_t *, void *);
    } __sigaction_handler;
    __sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  }
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = signal_handler;
  //int sigemptyset(sigset_t *set);
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGINT, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGINT failed: %s\n", strerror(errno));
    //exit(1);
  }

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGTERM, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGTERM failed: %s\n", strerror(errno));
    //exit(1);
  }

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGQUIT, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGQUIT failed: %s\n", strerror(errno));
    //exit(1);
  }

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGKILL, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGKILL failed: %s\n", strerror(errno));
    //exit(1);
  }

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGSTOP, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGSTOP failed: %s\n", strerror(errno));
    //exit(1);
  }

  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);

    sleep(1);
  }

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
}
