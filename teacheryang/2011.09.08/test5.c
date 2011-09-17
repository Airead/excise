#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

int global_value = 0;
char *global_buf;
int global_fd = -1;

void *func(void *arg);
void cleanup_func(void *arg);
void cleanup_func2(void *arg);

int main(int argc, char **argv)
{
  pthread_t tid;
  int code;

  code = pthread_create(&tid, NULL, func, NULL);

  if (code != 0)
  {
    fprintf(stderr, "Create new thread failed: %s\n", strerror(code));
    exit(1);
  }

  sleep(2);

  pthread_cancel(tid);

  pthread_join(tid, NULL);

  fprintf(stdout, "global_value = %d\n", global_value);

  sleep(1000);

  pthread_exit((void *) 0);
}

void *func(void *arg)
{
  int oldstate;

  // int pthread_setcancelstate(int state, int *oldstate);
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);

  global_buf = malloc(1024);

  //int open(const char *pathname, int flags, mode_t mode);
  global_fd = open("./test.file", O_RDONLY | O_CREAT, 0644);

  sleep(3);

  //void pthread_cleanup_push(void (*routine) (void *), void *arg);
  pthread_cleanup_push(cleanup_func, NULL);
  pthread_cleanup_push(cleanup_func2, NULL);

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);

  int i;

  for (i = 0; i < 5; i++)
  {
    global_value = 1000;

    // ssize_t write(int fd, const void *buf, size_t count);
    write(1, "x", 1);

    sleep(1);
  }

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);

  free(global_buf);
  global_buf = NULL;

  fprintf(stdout, "global_buf freed.\n");

  close(global_fd);

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);

  //void pthread_cleanup_pop(int execute);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);

  pthread_exit((void *) 0);
}

void cleanup_func(void *arg)
{
  fprintf(stdout, "cleanup function called.\n");
  free(global_buf);
}

void cleanup_func2(void *arg)
{
  fprintf(stdout, "cleanup function 2 called.\n");
  global_value = 9;

  close(global_fd);
}
