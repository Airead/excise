#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int length;

  //long int strtol(const char *nptr, char **endptr, int base);
  length = strtol(argv[2], NULL, 10);

  fprintf(stdout, "Are you sure truncate file %s to %d bytes?[y/n]", argv[1], length);
  fflush(stdout);

  long line_max;

  /* LINE_MAX - _SC_LINE_MAX
   * The  maximum  length  of a utility’s input line length,
   * either  from  standard  input  or  from  a  file.  This
   * includes length for a trailing newline.
   */

  //long sysconf(int name);
  line_max = sysconf(_SC_LINE_MAX);

  char *buffer = NULL;

  //void *malloc(size_t size);
  if ((buffer = (char *) malloc(line_max)) == NULL)
  {
    fprintf(stderr, "Allocate memory for buffer failed, request size = %ld\n", line_max);
    exit(1);
  }

  ssize_t n;

  memset(buffer, 0, line_max);

  //ssize_t read(int fd, void *buf, size_t count);
  if ((n = read(0, buffer, line_max - 1)) < 0)
  {
    fprintf(stderr, "Read from stdin failed: %s\n", strerror(errno));

    free(buffer);
    buffer = NULL;

    exit(1);
  }

  //buffer[n] = '\0';

  fprintf(stdout, "User input: %s\n", buffer);

  // TODO: Parse user input, if user input "yes" or "y", continue, else exit.

  if (0)
  {
    //int ftruncate(int fd, off_t length);
    //int truncate(const char *path, off_t length);
    if (truncate(argv[1], length) < 0)
    {
      fprintf(stderr, "Truncate size of file %s to %d failed: %s\n", argv[1], length, strerror(errno));
      exit(1);
    }

    fprintf(stdout, "Size of file %s truncated to %d byte(s).\n", argv[1], length);
  }

  free(buffer);
  buffer = NULL;

  return 0;
}
