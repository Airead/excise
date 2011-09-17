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

  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL, 0644)) < 0)
  {
    //EEXIST pathname already exists and O_CREAT and O_EXCL were used.
    if (errno == EEXIST)
    {
      // file exists, just open it
      fprintf(stdout, "File %s exists, just open it.\n", argv[1]);

      //int open(const char *pathname, int flags);
      if ((fd = open(argv[1], O_RDONLY)) < 0)
      {
	fprintf(stderr, "Open file %s for reading failed: %s\n", argv[1], strerror(errno));
	exit(1);
      }
    }
    else
    {
      fprintf(stderr, "Open(Create) file %s for reading failed: %s\n", argv[1], strerror(errno));
      exit(1);
    }
  }

  fprintf(stdout, "Open/Create file %s for reading successfully.\n", argv[1]);

  close(fd);

  return 0;
}
