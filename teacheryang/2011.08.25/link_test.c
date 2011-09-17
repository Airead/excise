#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int link(const char *oldpath, const char *newpath);
  if (link(argv[1], argv[2]) < 0)
  {
    fprintf(stderr, "Make hard link %s -> %s failed: %s\n", argv[2], argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Make new hard link %s -> %s successfully.\n", argv[2], argv[1]);

  return 0;
}
