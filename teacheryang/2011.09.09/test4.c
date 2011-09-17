#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int global_value = 0;
pthread_mutex_t global_value_mutex;

void *monitor(void *arg);
void *inc(void *arg);

int main(int argc, char **argv)
{
  pthread_t t1, t2;
  int rc;

  //int pthread_mutex_init(pthread_mutex_t * restrict mutex, const pthread_mutexattr_t * restrict attr);
  pthread_mutex_init(&global_value_mutex, NULL);

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  rc = pthread_create(&t1, NULL, monitor, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create monitor thread: %s\n", strerror(rc));
  }

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  rc = pthread_create(&t2, NULL, inc, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create inc thread: %s\n", strerror(rc));
  }

  //int pthread_join(pthread_t thread, void **value_ptr);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  //int pthread_mutex_destroy(pthread_mutex_t * mutex);
  pthread_mutex_destroy(&global_value_mutex);

  pthread_exit((void *) 0);
}

void *inc(void *arg)
{
  for (;;)
  {
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    pthread_mutex_lock(&global_value_mutex);

    global_value++;

    fprintf(stdout, "INC: %d\n", global_value);

    //int pthread_mutex_unlock(pthread_mutex_t *mutex);
    pthread_mutex_unlock(&global_value_mutex);

    sleep(1);
  }

  pthread_exit((void *) 0);
}

void *monitor(void *arg)
{
  for (;;)
  {
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    pthread_mutex_lock(&global_value_mutex);

    if (global_value > 10)
    {
      fprintf(stdout, "Do something here.\n");
    }

    //int pthread_mutex_unlock(pthread_mutex_t *mutex);
    pthread_mutex_unlock(&global_value_mutex);

    sleep(1);
  }

  pthread_exit((void *) 0);
}
