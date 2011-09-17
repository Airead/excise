#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig);
void output_signals(sigset_t * s);
void output_blocked_signals(void);
void output_pending_signals(void);

int main(int argc, char **argv)
{
  signal(SIGINT, signal_handler);

  sigset_t s, o;

  //int sigemptyset(sigset_t *set);
  sigemptyset(&s);

  //int sigaddset(sigset_t *set, int signum);
  sigaddset(&s, SIGINT);
  sigaddset(&s, SIGQUIT);
  sigaddset(&s, SIGTERM);

  //int sigprocmask(int how, const sigset_t * set, sigset_t * oldset);
  if (sigprocmask(SIG_BLOCK, &s, &o) < 0)
  {
    // sigprocmask() returns 0 on success and -1 on error.
    fprintf(stderr, "[%d]Set new signal mask failed: %s\n", getpid(), strerror(errno));
    exit(1);
  }

  raise(SIGINT);
  raise(SIGQUIT);
  raise(SIGTERM);

  pid_t pid;

  if ((pid = fork()) < 0)
  {
    // failed
    fprintf(stderr, "fork() failed: %s\n", strerror(errno));
    exit(1);
  }
  else if (pid == 0)
  {
    // child process
    output_blocked_signals();
    output_pending_signals();

#if 0
    for (;;)
    {
      fprintf(stdout, "+");
      fflush(stdout);

      sleep(1);
    }
#endif

    exit(0);
  }
  else
  {
    // parent process
    output_blocked_signals();
    output_pending_signals();

#if 0
    for (;;)
    {
      fprintf(stdout, "*");
      fflush(stdout);

      sleep(1);
    }
#endif
  }

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stdout, "[%d]Caught signal %d.\n", getpid(), sig);
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
