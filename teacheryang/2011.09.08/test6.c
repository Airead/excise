#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *func(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid;
  pthread_attr_t attr;
  int code;

  //int pthread_attr_init(pthread_attr_t * attr);
  pthread_attr_init(&attr);

  //int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
  //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  code = pthread_create(&tid, &attr, func, NULL);

  if (code != 0)
  {
    fprintf(stderr, "Create thread failed: %s\n", strerror(code));
    exit(1);
  }

  //int pthread_attr_destroy(pthread_attr_t * attr);
  pthread_attr_destroy(&attr);

  //int pthread_detach(pthread_t thread);
  code = pthread_detach(tid);

  if (code != 0)
  {
    fprintf(stderr, "Detach thread failed: %s\n", strerror(code));
    exit(1);
  }

  sleep(1);

  int status;

  //int pthread_join(pthread_t thread, void **value_ptr);
  code = pthread_join(tid, (void *) &status);

  if (code != 0)
  {
    fprintf(stderr, "Join thread failed: %s\n", strerror(code));
    exit(1);
  }

  fprintf(stdout, "Thread 0x%08x terminated, status = %d.\n", tid, status);

  pthread_exit((void *) 0);
}

void *func(void *arg)
{
#if 0
  int code;

  //int pthread_detach(pthread_t thread);
  code = pthread_detach(pthread_self());

  if (code != 0)
  {
    fprintf(stderr, "Detach thread failed: %s\n", strerror(code));
    exit(1);
  }
#endif

  sleep(5);

  pthread_exit((void *) 987);
  //return 56;
}
