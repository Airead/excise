#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye(void)
{
  printf("That was all, folks\n");
}

void foo(void)
{
  printf("%s:%d: Call foo().\n", __FILE__, __LINE__);
}

void print_value(int x, void *value)
{
  fprintf(stdout, "x = %d, value = %d\n", x, (int) value);
}

int main(int argc, char **argv)
{
  long a;
  int i;

  a = sysconf(_SC_ATEXIT_MAX);
  printf("ATEXIT_MAX = %ld\n", a);

  i = atexit(bye);

  if (i != 0)
  {
    fprintf(stderr, "cannot set exit function\n");
    return EXIT_FAILURE;
  }

  atexit(foo);

  //int on_exit(void (*function)(int , void *), void *arg);
  on_exit(print_value, (int *) 1);
  on_exit(print_value, (int *) 2);

#if 0
  bye();
#endif

  return 8765;
}
