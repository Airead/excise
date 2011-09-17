#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

typedef void (*sighandler_t) (int);
void signal_handler(int s);

int main(int argc, char **argv)
{
  sighandler_t original;

  //sighandler_t signal(int signum, sighandler_t handler);
  if ((original = signal(SIGKILL, signal_handler)) == SIG_ERR)
  {
    fprintf(stderr, "Set new handler for SIGKILL failed: %s\n", strerror(errno));
    //exit(1);
  }

  //sighandler_t signal(int signum, sighandler_t handler);
  if ((original = signal(SIGSTOP, signal_handler)) == SIG_ERR)
  {
    fprintf(stderr, "Set new handler for SIGSTOP failed: %s\n", strerror(errno));
    //exit(1);
  }

  //sighandler_t signal(int signum, sighandler_t handler);
  if ((original = signal(SIGINT, signal_handler)) == SIG_ERR)
  {
    fprintf(stderr, "Set new handler for SIGINT failed: %s\n", strerror(errno));
    //exit(1);
  }

  fprintf(stdout, "Set new handler for SIGINT successfully\n");

  return 0;
}

void signal_handler(int s)
{
  fprintf(stdout, "Caught signal %d.\n", s);
}
