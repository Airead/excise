#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int s);

int main(int argc, char **argv)
{
  sigset_t s, o;

  signal(SIGINT, signal_handler);
  signal(SIGQUIT, signal_handler);
  signal(SIGTERM, signal_handler);

#if 0
  int sigfillset(sigset_t * set);
  int sigdelset(sigset_t * set, int signum);
#endif

  //int sigemptyset(sigset_t * set);
  sigemptyset(&s);

  //int sigaddset(sigset_t * set, int signum);
  sigaddset(&s, SIGINT);
  sigaddset(&s, SIGQUIT);
  sigaddset(&s, SIGTERM);

  sigaddset(&s, SIGKILL);
  sigaddset(&s, SIGSTOP);

  //int sigprocmask(int how, const sigset_t * set, sigset_t * oldset);
  if (sigprocmask(SIG_BLOCK, &s, &o) < 0)
  {
    fprintf(stderr, "Change signal mask failed: %s\n", strerror(errno));
    exit(1);
  }

  int count = 30;

  for (;;)
  {
#if 0
    fprintf(stdout, ".");
    fflush(stdout);
#endif

    sigset_t p;

    //int sigpending(sigset_t *set);
    sigpending(&p);

    int i;

    for (i = 1; i <= 64; i++)
    {
      //int sigismember(const sigset_t * set, int signum);
      if (sigismember(&p, i))
      {
	fprintf(stdout, "+");
      }
      else
      {
	fprintf(stdout, "-");
      }
    }

    fprintf(stdout, "\n");

    if (count-- <= 0)
    {
      sigset_t remove_set;

      sigemptyset(&remove_set);
      sigaddset(&remove_set, SIGINT);
      sigaddset(&remove_set, SIGTERM);
      sigaddset(&remove_set, SIGQUIT);

      sigprocmask(SIG_UNBLOCK, &remove_set, NULL);
    }

    sleep(1);
  }

  return 0;
}

void signal_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);
}
