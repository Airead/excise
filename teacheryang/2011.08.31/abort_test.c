#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int sig);

int main(int argc, char **argv)
{
  signal(SIGABRT, signal_handler);

  //void abort(void);
  abort();

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stdout, "Caught signal %d\n", sig);

#if 0
  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);

    sleep(1);
  }
#endif
}
