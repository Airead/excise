#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int putenv(char *string);
  if (putenv(argv[1]) != 0)
  {
    fprintf(stderr, "putenv() failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "AAAA: %s\n", getenv("AAAA"));

  return 0;
}
