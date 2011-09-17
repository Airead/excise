#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  if ((fd = open(argv[1], O_RDONLY)) < 0)
  {
    fprintf(stderr, "Open FIFO file %s for reading failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open FIFO file %s for reading successfully\n", argv[1]);

  char buffer[BUFFER_SIZE];
  ssize_t n;

  for (;;)
  {
    //ssize_t read(int fd, void *buf, size_t count);
    if ((n = read(fd, buffer, sizeof(buffer) - 1)) < 0)
    {
      // error
      fprintf(stderr, "Read from FIFO failed: %s\n", strerror(errno));
      break;
    }
    else if (n == 0)
    {
      // write end closed
      fprintf(stdout, "Write end closed\n");
      close(fd);
      break;
    }
    else
    {
      // read n bytes from FIFO
      buffer[n] = '\0';
      fprintf(stdout, "Read %d bytes from FIFO: %s\n", n, buffer);
    }
  }

  close(fd);

  return 0;
}
