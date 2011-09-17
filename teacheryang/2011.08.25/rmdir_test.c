#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int rmdir(const char *pathname);
  if (rmdir(argv[1]) < 0)
  {
    fprintf(stderr, "Cannot remove directory %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Directory %s removed.\n", argv[1]);

  return 0;
}
