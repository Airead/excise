#include <stdio.h>
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

  //int pthread_attr_getdetachstate(const pthread_attr_t * attr, int *detachstate);
  //int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  //int pthread_attr_getstackaddr(const pthread_attr_t * restrict attr, void **restrict stackaddr);
  //int pthread_attr_setstackaddr(pthread_attr_t * attr, void *stackaddr);

  size_t size;

  //int pthread_attr_getstacksize(const pthread_attr_t * restrict attr, size_t * restrict stacksize);
  pthread_attr_getstacksize(&attr, &size);

  fprintf(stdout, "stacksize = %d\n", size);

  //int pthread_attr_setstacksize(pthread_attr_t * attr, size_t stacksize);
  if ((code = pthread_attr_setstacksize(&attr, 2 * size)) != 0)
  {
    fprintf(stderr, "set stack size failed: %s\n", strerror(code));
    // FIXME: How to do?
  }

#if 0
  pthread_attr_getstacksize(&attr, &size);
  fprintf(stdout, "stacksize = %d\n", size);
#endif

  //int pthread_attr_getstack(const pthread_attr_t * restrict attr, void **restrict stackaddr, size_t * restrict stacksize);
  //int pthread_attr_setstack(pthread_attr_t * attr, void *stack - addr, size_t stacksize);

#if 0
  void *p;

  if ((p = malloc(1024 * 1024 * 20)) == NULL)
  {
    // failed
    fprintf(stdout, "Allocate memory failed\n");
    exit(1);
  }

  code = pthread_attr_setstack(&attr, p, 1024 * 1024 * 20);

  if (code != 0)
  {
    fprintf(stderr, "setstack failed: %s\n", strerror(code));
  }
#endif

  //int pthread_attr_getschedpolicy(const pthread_attr_t * restrict attr, int *restrict policy);
  //int pthread_attr_setschedpolicy(pthread_attr_t * attr, int policy);

  //int pthread_attr_getschedparam(const pthread_attr_t * restrict attr, struct sched_param *restrict param);
  //int pthread_attr_setschedparam(pthread_attr_t * restrict attr, const struct sched_param *restrict param);


  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  code = pthread_create(&tid, &attr, func, NULL);

  if (code != 0)
  {
    // failed
    fprintf(stderr, "Create new thread failed: %s\n", strerror(code));
    exit(1);
  }

  fprintf(stdout, "Created a new thread.\n");

  //int pthread_attr_destroy(pthread_attr_t * attr);
  pthread_attr_destroy(&attr);

  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  pthread_exit((void *) 0);
}
