#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  fprintf(stdout, "Effective UID: %d, Effective GID: %d\n", geteuid(), getegid());

  //int mkdir(const char *pathname, mode_t mode);
  if (mkdir(argv[1], 0755) < 0)
  {
    fprintf(stderr, "Cannot create new directory %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "New directory %s created.\n", argv[1]);

  return 0;
}
