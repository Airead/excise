#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void *func(void *arg);
void signal_handler(int sig);
void main_signal_handler(int sig);
void output_sigset(sigset_t * s);

int main(int argc, char **argv)
{
  sigset_t s, o;

  //int sigemptyset(sigset_t * set);
  sigemptyset(&s);

  //int sigaddset(sigset_t * set, int signum);
  //sigaddset(&s, SIGINT);
  sigaddset(&s, SIGTERM);
  sigaddset(&s, SIGQUIT);

  //int pthread_sigmask(int how, const sigset_t * restrict set, sigset_t * restrict oset);
  if (pthread_sigmask(SIG_BLOCK, &s, &o) < 0)
  {
    fprintf(stderr, "Change thread's signal mask failed: %s\n", strerror(errno));
    exit(1);
  }

  //raise(SIGINT);
  raise(SIGTERM);

  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    void (*sa_handler) (int);
    void (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  }
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = main_signal_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGINT, &act, &oact) < 0)
  {
    fprintf(stderr, "Set signal handler for thread failed: %s\n", strerror(errno));
  }

  pthread_t tid;
  int code;

  pthread_t main_tid = pthread_self();

  fprintf(stdout, "main_tid = 0x%08x\n", pthread_self());

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  code = pthread_create(&tid, NULL, func, (void *) &main_tid);

  if (code != 0)
  {
    fprintf(stderr, "Create new thread failed: %s\n", strerror(code));
    exit(1);
  }

  pthread_join(tid, NULL);

  fprintf(stdout, "after join\n");

  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  pthread_t main_tid = *(pthread_t *) arg;
  fprintf(stdout, "main_tid = 0x%08x\n", main_tid);

#if 0
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    void (*sa_handler) (int);
    void (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  }
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = signal_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGINT, &act, &oact) < 0)
  {
    fprintf(stderr, "Set signal handler for thread failed: %s\n", strerror(errno));
  }
#endif

  sigset_t c;

  //int pthread_sigmask(int how, const sigset_t * restrict set, sigset_t * restrict oset);
  pthread_sigmask(SIG_BLOCK, NULL, &c);

  fprintf(stdout, "Blocked signals: ");
  output_sigset(&c);

  sigset_t p;

  //int sigpending(sigset_t *set);
  sigpending(&p);

  fprintf(stdout, "Pending signals: ");
  output_sigset(&p);

  //int pthread_kill(pthread_t thread, int sig);
  int code = pthread_kill(main_tid, SIGINT);

  if (code != 0)
  {
    fprintf(stderr, "pthread_kill() failed: %s\n", strerror(code));
  }

  for (;;)
  {
    write(1, "x", 1);
    sleep(1);
  }

  pthread_exit((void *) 0);
}

void output_sigset(sigset_t * s)
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

void signal_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
}

void main_signal_handler(int sig)
{
  fprintf(stdout, "Caught signal %d by main().\n", sig);
}
