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
  int value = 9;

  //int pthread_create(pthread_t * restrict thread, const pthread_attr_t * restrict attr, void *(*start_routine) (void *), void *restrict arg);
  code = pthread_create(&tid, NULL, func, (void *) &value);

  if (code != 0)
  {
    fprintf(stderr, "Cannot create new thread: %s\n", strerror(code));
    exit(1);
  }

  fprintf(stdout, "Create a new thread 0x%08x\n", tid);

  fprintf(stdout, "[0x%08x] PID: %d, PPID: %d, PGID: %d, SID: %d\n", pthread_self(), getpid(), getppid(), getpgid(0), getsid(0));
  fprintf(stdout, "[0x%08x] UID: %d, EUID: %d\n", pthread_self(), getuid(), geteuid());

  //BAD manner: return 0;
  //void pthread_exit(void *value_ptr);
  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  int value = *(int *) arg;

  fprintf(stdout, "[0x%08x] PID: %d, PPID: %d, PGID: %d, SID: %d\n", pthread_self(), getpid(), getppid(), getpgid(0), getsid(0));
  fprintf(stdout, "[0x%08x] UID: %d, EUID: %d\n", pthread_self(), getuid(), geteuid());

  fprintf(stdout, "value = %d\n", value);
  return (void *) 0;
}
