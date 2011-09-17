#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREADS_NUM	20

int global_value = 0;
pthread_mutex_t global_value_mutex;

void *reader(void *arg);
void *writer(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid[THREADS_NUM];
  int rc;
  int i;

  //void srand(unsigned int seed);
  srand(47);

  pthread_mutex_init(&global_value_mutex, NULL);

  for (i = 0; i < THREADS_NUM; i++)
  {
    if (i % 8 == 0)
    {
      //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
      rc = pthread_create(&tid[i], NULL, writer, (void *) i);
    }
    else
    {
      rc = pthread_create(&tid[i], NULL, reader, (void *) i);
    }

    if (rc != 0)
    {
      fprintf(stderr, "Failed to create thread #%d: %s\n", i, strerror(rc));
    }
  }

  for (i = 0; i < THREADS_NUM; i++)
  {
    //int pthread_join(pthread_t thread, void **value_ptr);
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&global_value_mutex);

  pthread_exit((void *) 0);
}

void *writer(void *arg)
{
  int id = (int) arg;

  for (;;)
  {
    pthread_mutex_lock(&global_value_mutex);

    global_value += id;
    fprintf(stdout, "[W]#%02d: global_value = %d\n", id, global_value);

    pthread_mutex_unlock(&global_value_mutex);

    sleep(rand() % 5);
  }

  pthread_exit((void *) 0);
}

void *reader(void *arg)
{
  int id = (int) arg;

  for (;;)
  {
    pthread_mutex_lock(&global_value_mutex);
    fprintf(stdout, "[R]#%02d: global_value = %d\n", id, global_value);
    pthread_mutex_unlock(&global_value_mutex);

    //int rand(void);
    sleep(rand() % 3);
  }

  pthread_exit((void *) 0);
}
