#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void output_signals(sigset_t * s);
void output_blocked_signals(void);
void output_pending_signals(void);

int main(int argc, char **argv)
{
  output_blocked_signals();
  output_pending_signals();

  return 0;
}

void output_signals(sigset_t * s)
{
  int i;

  for (i = 1; i <= 64; i++)
  {
    // int sigismember(const sigset_t *set, int signum);
    if (sigismember(s, i))
    {
      fprintf(stdout, "+");
    }
    else
    {
      fprintf(stdout, "-");
    }
  }

  fprintf(stdout, "\n");
}

void output_blocked_signals(void)
{
  fprintf(stdout, "[%d]Blocked signals: ", getpid());

  sigset_t c;

  //int sigprocmask(int how, const sigset_t * set, sigset_t * oldset);
  sigprocmask(SIG_BLOCK, NULL, &c);

  output_signals(&c);
}

void output_pending_signals(void)
{
  fprintf(stdout, "[%d]Pending signals: ", getpid());

  sigset_t p;

  //int sigpending(sigset_t *set);
  sigpending(&p);

  output_signals(&p);
}
