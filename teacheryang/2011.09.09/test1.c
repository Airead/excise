#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define THREADS_NUM	20

void output_signals(sigset_t * s);
void output_blocked_signals(int id);
void output_pending_signals(int id);

void *func(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid[THREADS_NUM];
  pthread_attr_t attr;
  int i;
  int code;

  sigset_t s, o;

  //int sigemptyset(sigset_t * set);
  sigemptyset(&s);

  //int sigaddset(sigset_t * set, int signum);
  sigaddset(&s, SIGINT);
  sigaddset(&s, SIGQUIT);
  sigaddset(&s, SIGTERM);

  //int sigprocmask(int how, const sigset_t * restrict set, sigset_t * restrict oset);
  sigprocmask(SIG_BLOCK, &s, &o);

  //int pthread_attr_init(pthread_attr_t * attr);
  pthread_attr_init(&attr);

  //int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // FIXME: set other attributes

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  for (i = 0; i < THREADS_NUM; i++)
  {
    code = pthread_create(&tid[i], &attr, func, (void *) i);

    if (code != 0)
    {
      fprintf(stderr, "Failed to create new thread #%d: %s\n", i, strerror(code));
    }
  }

  for (i = 0; i < THREADS_NUM; i++)
  {
    //int pthread_join(pthread_t thread, void **value_ptr);
    pthread_join(tid[i], NULL);
  }

  //int pthread_attr_destroy(pthread_attr_t * attr);
  pthread_attr_destroy(&attr);

  return 0;
}

void *func(void *arg)
{
  int id = (int) arg;

  for (;;)
  {
    //output_blocked_signals(id);
    output_pending_signals(id);

    sleep(2);
  }

  pthread_exit((void *) 0);
}

void output_pending_signals(int id)
{
  fprintf(stdout, "[%02d]Pending signals: ", id);

  sigset_t p;

  //int sigpending(sigset_t *set);
  sigpending(&p);

  output_signals(&p);
}

void output_blocked_signals(int id)
{
  fprintf(stdout, "[%02d]Blocked signals: ", id);

  sigset_t c;

  //int sigprocmask(int how, const sigset_t * set, sigset_t * oldset);
  sigprocmask(SIG_BLOCK, NULL, &c);

  output_signals(&c);
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
