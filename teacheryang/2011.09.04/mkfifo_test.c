#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int mkfifo(const char *pathname, mode_t mode);
  if (mkfifo(argv[1], 0644) < 0)
  {
    fprintf(stderr, "Cannot create new FIFO file: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new FIFO file %s.\n", argv[1]);

  return 0;
}
