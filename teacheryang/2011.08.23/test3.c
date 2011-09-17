#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
  struct winsize size;

#if 0
  if (isatty(STDOUT_FILENO) == 0)
  {
    fprintf(stderr, "isatty() failed: %s\n", strerror(errno));
    exit(1);
  }
#endif

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
  {
    fprintf(stderr, "ioctl TIOCGWINSZ error: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "%d rows, %d columns\n", size.ws_row, size.ws_col);

  return 0;
}
