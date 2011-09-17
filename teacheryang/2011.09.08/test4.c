#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *func(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid;
  int code;

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  code = pthread_create(&tid, NULL, func, NULL);

  if (code != 0)
  {
    fprintf(stderr, "Create thread failed: %s\n", strerror(code));
    exit(1);
  }

  sleep(3);

  //int pthread_cancel(pthread_t thread);
  pthread_cancel(tid);

  //int pthread_join(pthread_t thread, void **value_ptr);
  pthread_join(tid, NULL);

  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  int oldstate;

  //int pthread_setcancelstate(int state, int *oldstate);
  //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);

  int oldtype;

  //int pthread_setcanceltype(int type, int *oldtype);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
  //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &oldtype);

  int i;

  for (i = 0;; i++)
  {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);

    //fprintf(stdout, "+");
    //fflush(stdout);
    write(1, "+", 1);

    //sleep(1);

    //fprintf(stdout, "-");
    //fflush(stdout);

    write(1, "-", 1);

#if 0
    if (i > 5)
    {
      //int pthread_setcancelstate(int state, int *oldstate);
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    }
#endif

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);

    //void pthread_testcancel(void);
    pthread_testcancel();
  }

  pthread_exit((void *) 0);
}
