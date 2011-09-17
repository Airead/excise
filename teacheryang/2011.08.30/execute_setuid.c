#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  char *v[] = { "./print_ids", NULL };

  //int execv(const char *path, char *const argv[]);
  if (execv("./print_ids", v) < 0)
  {
    fprintf(stderr, "Execute './print_ids' failed: %s\n", strerror(errno));
    exit(1);
  }

  return 0;
}
