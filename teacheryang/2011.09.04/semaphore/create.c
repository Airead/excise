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
  int value;

  value = (int) strtol(argv[2], NULL, 10);

  //sem_t *sem_open(const char *name, int oflag);
  //sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

  if ((s = sem_open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644, value)) == SEM_FAILED)
  {
    fprintf(stderr, "Cannot create new POSIX named sempahore: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new POSIX named sempahore %s\n", argv[1]);

  //int sem_close(sem_t *sem);
  sem_close(s);

  return 0;
}
