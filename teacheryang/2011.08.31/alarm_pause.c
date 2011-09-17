#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int s);

int main(int argc, char **argv)
{
  signal(SIGALRM, signal_handler);

  alarm(5);

  // int pause(void);
  pause();

  fprintf(stdout, "Can I go here?\n");

  return 0;
}

void signal_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);
}
