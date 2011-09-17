#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int global_value = 0;

//pthread_mutex_t global_value_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t global_value_mutex;

void *writer(void *arg);
void *reader(void *arg);

int main(int argc, char **argv)
{
  pthread_mutexattr_t mutexattr;

  //int pthread_mutexattr_init(pthread_mutexattr_t * attr);
  pthread_mutexattr_init(&mutexattr);

  //int pthread_mutexattr_settype(pthread_mutexattr_t * attr, int type);

  //------------------------------------------------------------------
  // Possible values:
  //
  //    PTHREAD_MUTEX_NORMAL
  //    PTHREAD_MUTEX_ERRORCHECK
  //    PTHREAD_MUTEX_RECURSIVE
  //    PTHREAD_MUTEX_DEFAULT
  //
  //------------------------------------------------------------------

  //int pthread_mutexattr_setpshared(pthread_mutexattr_t * attr, int pshared);
  //------------------------------------------------------------------
  // Possible values: 
  //
  //    PTHREAD_PROCESS_SHARED 
  //    PTHREAD_PROCESS_PRIVATE
  //
  //------------------------------------------------------------------

  //int pthread_mutexattr_setprotocol(pthread_mutexattr_t * attr, int protocol);
  //------------------------------------------------------------------
  // Possible values: 
  //
  //    PTHREAD_PRIO_NONE 
  //    PTHREAD_PRIO_INHERIT
  //    PTHREAD_PRIO_PROTECT
  //
  //------------------------------------------------------------------

  //int pthread_mutexattr_setprioceiling(pthread_mutexattr_t * attr, int prioceiling);

  //int pthread_mutex_init(pthread_mutex_t * restrict mutex, const pthread_mutexattr_t * restrict attr);
  pthread_mutex_init(&global_value_mutex, &mutexattr);

  //int pthread_mutexattr_destroy(pthread_mutexattr_t * attr);
  pthread_mutexattr_destroy(&mutexattr);

  pthread_t t1, t2;
  int rc;

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  rc = pthread_create(&t1, NULL, writer, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create writer thread: %s\n", strerror(rc));
  }

  rc = pthread_create(&t2, NULL, reader, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create reader thread: %s\n", strerror(rc));
  }

  //int pthread_join(pthread_t thread, void **value_ptr);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  //int pthread_mutex_destroy(pthread_mutex_t * mutex);
  pthread_mutex_destroy(&global_value_mutex);

  pthread_exit((void *) 0);
}

void *writer(void *arg)
{
  for (;;)
  {
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    pthread_mutex_lock(&global_value_mutex);

    global_value++;

    //int pthread_mutex_unlock(pthread_mutex_t *mutex);
    pthread_mutex_unlock(&global_value_mutex);

    sleep(1);
  }

  pthread_exit((void *) 0);
}

void *reader(void *arg)
{
  for (;;)
  {
    //int pthread_mutex_lock(pthread_mutex_t *mutex);
    pthread_mutex_lock(&global_value_mutex);

    fprintf(stdout, "global_value = %d\n", global_value);

    //int pthread_mutex_unlock(pthread_mutex_t *mutex);
    pthread_mutex_unlock(&global_value_mutex);

    sleep(1);
  }

  pthread_exit((void *) 0);
}
