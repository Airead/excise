#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  //char *getenv(const char *name);
  fprintf(stdout, "HOME: %s\n", getenv("HOME"));
  return 0;
}
