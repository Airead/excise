#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>

int main(int argc, char **argv)
{
  fprintf(stdout, "Hello world");

  fflush(stdout);

  _exit(0);
}
