#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  if ((fd = open(argv[1], O_WRONLY)) < 0)
  {
    fprintf(stderr, "Open FIFO file %s for writing failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open FIFO file %s for writing successfully\n", argv[1]);

  //ssize_t write(int fd, const void *buf, size_t count);
  write(fd, argv[2], strlen(argv[2]));

  close(fd);

  return 0;
}
