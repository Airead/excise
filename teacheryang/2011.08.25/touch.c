#include <stdio.h>
#include <stdlib.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  // if file not exists, create a new one
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL, 0644)) < 0)
  {
    if (errno == EEXIST)
    {
      // file exists, change atime & mtime of file to current time
      // int utime(const char *filename, const struct utimbuf *buf);
      if (utime(argv[1], NULL) < 0)
      {
	fprintf(stderr, "Cannot change timestamp of file %s: %s\n", argv[1], strerror(errno));
	exit(1);
      }

      fprintf(stdout, "Timestamp of file %s changed.\n", argv[1]);
    }
    else
    {
      fprintf(stderr, "Cannot create new file %s: %s\n", argv[1], strerror(errno));
    }
  }

  return 0;
}
