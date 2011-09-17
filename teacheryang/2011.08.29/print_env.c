#include <stdio.h>

extern char **environ;

int main(int argc, char **argv)
{
  char **p;

  p = environ;

  while (p && *p)
  {
    fprintf(stdout, "%s\n", *p);
    p++;
  }

  return 0;
}
