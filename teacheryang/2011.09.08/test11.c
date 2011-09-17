#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *function(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid;
  pthread_attr_t attr;
  int code;

  //int pthread_attr_init(pthread_attr_t * attr);
  pthread_attr_init(&attr);

  //int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  //int pthread_attr_setstacksize(pthread_attr_t * attr, size_t stacksize);
  pthread_attr_setstacksize(&attr, 1024 * 1024 * 32);

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  if ((code = pthread_create(&tid, &attr, function, NULL)) != 0)
  {
    fprintf(stderr, "Create thread failed: %s\n", strerror(code));
    //int pthread_attr_destroy(pthread_attr_t * attr);
    pthread_attr_destroy(&attr);
    exit(1);
  }

  fprintf(stdout, "Create a new thread 0x%08lx\n", tid);

  //int pthread_attr_destroy(pthread_attr_t * attr);
  pthread_attr_destroy(&attr);

  sleep(3);

  //int pthread_cancel(pthread_t thread);
  if ((code = pthread_cancel(tid)) != 0)
  {
    fprintf(stderr, "Cancel thread 0x%08lx failed: %s\n", tid, strerror(code));
  }
  else
  {
    fprintf(stdout, "Thread 0x%08lx canceled.\n", tid);
  }

  pthread_exit((void *) 0);
}

void *function(void *arg)
{
  //fprintf(stdout, "Do something here.\n");

#if 0
  void pthread_testcancel(void);
#endif

  int oldstate;

  // PTHREAD_CANCEL_ENABLE and PTHREAD_CANCEL_DISABLE
  //int pthread_setcancelstate(int state, int *oldstate);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
  //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);

  int oldtype;

  //Legal values for type are  PTHREAD_CANCEL_DEFERRED and PTHREAD_CANCEL_ASYNCHRONOUS
  // int pthread_setcanceltype(int type, int *oldtype);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
  //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &oldtype);

  for (;;)
  {
    fprintf(stdout, "+");
    fflush(stdout);

    //void pthread_testcancel(void);
    //pthread_testcancel();

    fprintf(stdout, "-");
    fflush(stdout);

    //sleep(1);
  }

  pthread_exit(NULL);
}
