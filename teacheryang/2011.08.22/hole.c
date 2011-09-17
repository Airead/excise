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
  if ((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
  {
    fprintf(stderr, "Open file %s for r/w failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  off_t offset;

  //Upon successful completion, lseek() returns the resulting offset location
  //as measured in bytes from the beginning of the file.  Otherwise, a  value
  //of (off_t) -1 is returned and errno is set to indicate the error.

  //off_t lseek(int fd, off_t offset, int whence);
  if ((offset = lseek(fd, 1024-1, SEEK_SET)) == (off_t) - 1)
  {
    fprintf(stderr, "Reposition file offset failed: %s\n", strerror(errno));
  }

  fprintf(stdout, "New file offset is %d\n", (int)offset);

  //ssize_t write(int fd, const void *buf, size_t count);
  write(fd, "x", 1);

  close(fd);

  return 0;
}
