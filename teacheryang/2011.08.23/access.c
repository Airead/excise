#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //int access(const char *pathname, int mode);
  if (access(argv[1], F_OK) < 0)
  {
    if (errno == ENOENT)
    {
      fprintf(stdout, "File %s not exists.\n", argv[1]);
    }
    else
    {
      fprintf(stderr, "Cannot check permission on file %s: %s\n", argv[1], strerror(errno));
    }

    exit(1);
  }

  //int access(const char *pathname, int mode);
  if (access(argv[1], R_OK) < 0)
  {
    fprintf(stdout, "Read permission not granted to real uid.\n");
  }
  else
  {
    fprintf(stdout, "Read permission granted to real uid.\n");
  }

  //int access(const char *pathname, int mode);
  if (access(argv[1], W_OK) < 0)
  {
    fprintf(stdout, "Write permission not granted to real uid.\n");
  }
  else
  {
    fprintf(stdout, "Write permission granted to real uid.\n");
  }

  //int access(const char *pathname, int mode);
  if (access(argv[1], X_OK) < 0)
  {
    fprintf(stdout, "Execute permission not granted to real uid.\n");
  }
  else
  {
    fprintf(stdout, "Execute permission granted to real uid.\n");
  }

  return 0;
}
