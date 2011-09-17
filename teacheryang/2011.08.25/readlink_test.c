#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

int main(int argc, char **argv)
{
  char buffer[BUFFER_SIZE];
  ssize_t n;

  //ssize_t readlink(const char *path, char *buf, size_t bufsiz);
  if ((n = readlink(argv[1], buffer, sizeof(buffer) - 1)) < 0)
  {
    fprintf(stderr, "Read symbolic link value failed: %s\n", strerror(errno));
    exit(1);
  }

  buffer[n] = '\0';

  fprintf(stdout, "%s -> %s\n", argv[1], buffer);

  return 0;
}
