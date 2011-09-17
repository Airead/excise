#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //uid_t getuid(void);
  //uid_t geteuid(void);
  fprintf(stdout, "Real UID: %d, Effective UID: %d\n", getuid(), geteuid());

  mode_t mode;

  //long int strtol(const char *nptr, char **endptr, int base);
  mode = (mode_t) strtol(argv[2], NULL, 8);

  //int chmod(const char *path, mode_t mode);
  //int fchmod(int fildes, mode_t mode);
  if (chmod(argv[1], mode) < 0)
  {
    fprintf(stderr, "Change mode of file %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Mode changed.\n");

  return 0;
}
