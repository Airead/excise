#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int *global_address = NULL;

void *f1(void *arg);
void *f2(void *arg);

int main(int argc, char **argv)
{
  pthread_t t1, t2;
  int rc;

  rc = pthread_create(&t1, NULL, f1, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create thread #1: %s\n", strerror(rc));
  }

  rc = pthread_create(&t2, NULL, f2, NULL);

  if (rc != 0)
  {
    fprintf(stderr, "Failed to create thread #2: %s\n", strerror(rc));
  }

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_exit((void *) 0);
}

void *f1(void *arg)
{
  int f1_value = 99;
  int count = 0;

  global_address = &f1_value;

  for (;;)
  {
    fprintf(stdout, "f1_value = %d\n", f1_value);
    sleep(1);

    if (count++ > 10)
      break;
  }

  pthread_exit((void *) 0);
}

void *f2(void *arg)
{
  sleep(1);

  for (;;)
  {
    (*global_address)++;
    fprintf(stdout, "*global_address = %d\n", *global_address);
    sleep(1);
  }

  pthread_exit((void *) 0);
}
