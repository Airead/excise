#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  sem_t *s;

  //sem_t *sem_open(const char *name, int oflag);
  //sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
  if ((s = sem_open(argv[1], O_RDONLY)) == SEM_FAILED)
  {
    fprintf(stderr, "Cannot open POSIX named sempahore %s for reading: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open POSIX named sempahore %s successfully\n", argv[1]);

  int value;

  //int sem_getvalue(sem_t *sem, int *sval);
  sem_getvalue(s, &value);

  fprintf(stdout, "value = %d\n", value);

  //int sem_close(sem_t *sem);
  sem_close(s);

  return 0;
}
