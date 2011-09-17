#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int symlink(const char *oldpath, const char *newpath);
  if (symlink(argv[1], argv[2]) < 0)
  {
    fprintf(stderr, "Make symbolic link %s -> %s failed: %s\n", argv[2], argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Make symbolic link %s -> %s successfully\n", argv[2], argv[1]);

  return 0;
}
