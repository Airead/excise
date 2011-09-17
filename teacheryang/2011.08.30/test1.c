#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  char *str1 = "-a";

  //int execlp(const char *file, const char *arg, ...);
  if (execlp("ls", "ls", str1, "-l", "-h", NULL) < 0)
  {
    fprintf(stderr, "Execute 'ls' failed: %s\n", strerror(errno));
    exit(1);
  }

  return 0;
}
