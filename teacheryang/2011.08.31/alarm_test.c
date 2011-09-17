#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig);

int main(int argc, char **argv)
{
  signal(SIGALRM, signal_handler);

  //unsigned int alarm(unsigned int seconds);
  alarm(5);

  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);

    sleep(1);			// bad idea
  }

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
  //alarm(5);
}
