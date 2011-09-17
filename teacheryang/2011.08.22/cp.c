#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

// Usage: cp <source file> <target file>
int main(int argc, char **argv)
{
  int source_fd;
  int target_fd;

  //------------------------------------------------------------------
  // TODO: Implement following command line
  //
  //   cp [-f|--force] <-s|--source <source filename>> <-d|--target <target filename>>
  // 
  // Use getopt()/getopt_long() to parse command line arguments
  // You can use GNU gengetopt utility to generate command line arguments parser
  //------------------------------------------------------------------

  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s <source filename> <target filename>\n", argv[0]);
    exit(1);
  }

  // step 1, open source file for reading
  // int open(const char *pathname, int flags);
  if ((source_fd = open(argv[1], O_RDONLY)) < 0)
  {
    fprintf(stderr, "Open source file %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  // FIXME: step 1.5, get file mode from source file
  mode_t mode = 0644;

  // step 2, open target file for writing
  // int open(const char *pathname, int flags, mode_t mode);
  if ((target_fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, mode)) < 0)
  {
    if (errno == EEXIST)
    {
      // TODO: Ask user how to do? [overwrite or not?]
      fprintf(stderr, "Target file %s exists, do not overwrite, skip.\n", argv[1]);
      close(source_fd);
      exit(1);
    }

    fprintf(stderr, "Cannot open target file %s for writing: %s\n", argv[2], strerror(errno));

    close(source_fd);
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t read_bytes;
  ssize_t written_bytes;

  while (1)
  {
  read_again:
    // step 3, read from source file
    // ssize_t read(int fd, void *buf, size_t count);
    if ((read_bytes = read(source_fd, buffer, sizeof(buffer))) < 0)
    {
      // error
      if (errno == EINTR)
      {
	//EINTR  The call was interrupted by a signal before any data was read;
	goto read_again;
      }

      fprintf(stderr, "Read from source file %s failed: %s\n", argv[1], strerror(errno));
      break;
    }
    else if (read_bytes == 0)
    {
      // end of file
      break;
    }
    else
    {
      // read some data, write to target file
      // step 4, write to target file
      int total = 0;

      while (total < read_bytes)
      {
      write_again:
	// ssize_t write(int fd, const void *buf, size_t count);
	if ((written_bytes = write(target_fd, buffer + total, read_bytes - total)) < 0)
	{
	  // error
	  if (errno == EINTR)
	  {
	    goto write_again;
	  }

	  fprintf(stderr, "Write to target file %s failed: %s\n", argv[2], strerror(errno));
	  break;
	}
	else
	{
	  // success
	  fprintf(stdout, "Write %d bytes to target file.\n", written_bytes);

	  total += written_bytes;
	}
      }
    }
  }

  // step 5, close source file
  close(source_fd);

  // step 6, close target file
  close(target_fd);

  return 0;
}
