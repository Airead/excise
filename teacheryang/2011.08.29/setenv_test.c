#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  //int setenv(const char *name, const char *value, int overwrite);
  setenv(argv[1], argv[2], 1);

  fprintf(stdout, "%s: %s\n", argv[1], getenv(argv[1]));

  //int unsetenv(const char *name);
  return 0;
}
