#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int rename(const char *oldpath, const char *newpath);
  if (rename(argv[1], argv[2]) < 0)
  {
    fprintf(stderr, "Rename filename %s to %s failed: %s\n", argv[1], argv[2], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Renamed filename %s to %s.\n", argv[1], argv[2]);

  return 0;
}
