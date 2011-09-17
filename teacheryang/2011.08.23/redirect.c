#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644)) < 0)
  {
    fprintf(stderr, "Open file %s for writing failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  //int dup2(int oldfd, int newfd);
  dup2(fd, STDOUT_FILENO);

  printf("Hello world!\n");

  close(fd);

  sleep(1000);

  return 0;
}
