#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int global_value = 0;

void sigint_handler(int s);
void sigquit_handler(int s);

int main(int argc, char **argv)
{
  struct sigaction act, oact;

  memset(&act, 0, sizeof(act));

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

  act.sa_handler = sigint_handler;

  sigemptyset(&act.sa_mask);

  act.sa_flags = 0;
  act.sa_flags |= SA_NODEFER;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  sigaction(SIGINT, &act, &oact);

  act.sa_handler = sigquit_handler;

  sigaction(SIGQUIT, &act, &oact);

  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);
    sleep(1);
  }

  return 0;
}

void sigint_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);

  global_value++;
  fprintf(stdout, "global_value = %d.\n", global_value);

  int id = global_value;

  int i;
  int max;

  //void srand(unsigned int seed);
  srand(time(NULL));

  max = rand() % 10;

  for (i = 0; i < max; i++)
  {
    fprintf(stdout, "+");
    fflush(stdout);

    sleep(1);
  }

  fprintf(stdout, "id = %d.\n", id);
}

void sigquit_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);
}
