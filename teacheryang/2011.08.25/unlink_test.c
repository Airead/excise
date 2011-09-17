#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int unlink(const char *pathname);
  if (unlink(argv[1]) < 0)
  {
    fprintf(stderr, "unlink filename %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Filename %s unlinked.\n", argv[1]);

  return 0;
}
