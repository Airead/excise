#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// close()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  // step 1, open a new file, get a file descriptor
  //int open(const char *pathname, int flags);
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL, 0644)) < 0)
  {
    fprintf(stderr, "%s:%d: Open file %s for reading failed: %s\n", __FILE__, __LINE__, argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "%s:%d: Open file %s for reading successfully.\n", __FILE__, __LINE__, argv[1]);

  // step 2, use fcntl(F_DUPFD) 
  // Find  the  lowest  numbered  available  file descriptor
  // greater than or equal to arg and make it be a  copy  of
  // fd.
  int newfd;

  // int fcntl(int fd, int cmd, ... /* arg */ );
  if ((newfd = fcntl(fd, F_DUPFD, 100)) < 0)
  {
    fprintf(stderr, "%s:%d: Duplicate file descriptor failed: %s\n", __FILE__, __LINE__, strerror(errno));
  }
  else
  {
    fprintf(stdout, "%s:%d: Duplicated a new file descriptor, newfd = %d\n", __FILE__, __LINE__, newfd);
  }

  // step 3, use dup()
  int newfd2;

  // int dup(int oldfd);
  if ((newfd2 = dup(fd)) < 0)
  {
    fprintf(stderr, "%s:%d: Duplicate file descriptor failed: %s\n", __FILE__, __LINE__, strerror(errno));
  }
  else
  {
    fprintf(stdout, "%s:%d: Duplicated a new file descriptor, newfd = %d\n", __FILE__, __LINE__, newfd2);
  }

  // step 4, use dup2()
  int newfd3;

  // int dup2(int oldfd, int newfd);
  if ((newfd3 = dup2(fd, 4)) < 0)
  {
    fprintf(stderr, "%s:%d: Duplicate file descriptor failed: %s\n", __FILE__, __LINE__, strerror(errno));
  }
  else
  {
    fprintf(stdout, "%s:%d: Duplicated a new file descriptor, newfd = %d\n", __FILE__, __LINE__, newfd3);
  }

  // step 5, close files
  close(fd);
  close(newfd);
  close(newfd2);
  close(newfd3);

  return 0;
}
