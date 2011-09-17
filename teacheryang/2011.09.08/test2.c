#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define THREAD_NUM	5

void *func(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid[THREAD_NUM];
  int id[THREAD_NUM];
  int code;
  int i;

  for (i = 0; i < THREAD_NUM; i++)
  {
    id[i] = i;

    //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
    code = pthread_create(&tid[i], NULL, func, (void *) &id[i]);

    if (code != 0)
    {
      fprintf(stderr, "Cannot create new thread: %s\n", strerror(code));
      exit(1);
    }

    fprintf(stdout, "Create a new thread 0x%08x\n", tid[i]);

    //sleep(1);
  }

  //BAD manner: return 0;
  //void pthread_exit(void *value_ptr);
  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  int value = *(int *) arg;

  fprintf(stdout, "value = %d\n", value);

  return (void *) 0;
}
