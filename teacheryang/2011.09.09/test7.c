#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREADS_NUM	20

int global_value = 0;

//pthread_mutex_t global_value_mutex;
pthread_rwlock_t global_value_rwlock;

void *reader(void *arg);
void *writer(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid[THREADS_NUM];
  int rc;
  int i;

  //void srand(unsigned int seed);
  srand(47);

  //pthread_mutex_init(&global_value_mutex, NULL);
  //int pthread_rwlock_init(pthread_rwlock_t * restrict rwlock, const pthread_rwlockattr_t * restrict attr);
  pthread_rwlock_init(&global_value_rwlock, NULL);

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

  //pthread_mutex_destroy(&global_value_mutex);

  //int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
  pthread_rwlock_destroy(&global_value_rwlock);

  pthread_exit((void *) 0);
}

void *writer(void *arg)
{
  int id = (int) arg;
  int code;

  for (;;)
  {
    fprintf(stdout, "\033[0;34;28m[W]#%02d: Attempt to write ...\033[0m\n", id);

    //pthread_mutex_lock(&global_value_mutex);
    //int pthread_rwlock_trywrlock(pthread_rwlock_t * rwlock);
    //int pthread_rwlock_wrlock(pthread_rwlock_t * rwlock);
    code = pthread_rwlock_wrlock(&global_value_rwlock);

    if (code != 0)
    {
      fprintf(stdout, "\033[0;34;33m[W]#%02d: failed: %s \033[0m\n", id, strerror(code));

      //sleep(rand() % 2);
      continue;
    }

    global_value += id;
    global_value++;

    fprintf(stdout, "\033[0;32;40m[W]#%02d: global_value = %d\033[0m\n", id, global_value);

    //sleep(rand() % 2);

    //pthread_mutex_unlock(&global_value_mutex);
    //int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
    pthread_rwlock_unlock(&global_value_rwlock);

    sleep(rand() % 2);
  }

  pthread_exit((void *) 0);
}

void *reader(void *arg)
{
  int id = (int) arg;

  for (;;)
  {
    //pthread_mutex_lock(&global_value_mutex);

    //int pthread_rwlock_rdlock(pthread_rwlock_t * rwlock);
    //int pthread_rwlock_tryrdlock(pthread_rwlock_t * rwlock);
    pthread_rwlock_rdlock(&global_value_rwlock);

    fprintf(stdout, "[R]#%02d: global_value = %d\n", id, global_value);

    //sleep(rand() % 5);

    //pthread_mutex_unlock(&global_value_mutex);
    //int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
    pthread_rwlock_unlock(&global_value_rwlock);

    //int rand(void);
    sleep(rand() % 3 + 1);
  }

  pthread_exit((void *) 0);
}
