#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int sig;

  //long int strtol(const char *nptr, char **endptr, int base);
  pid = (pid_t) strtol(argv[1], NULL, 10);
  sig = (int) strtol(argv[2], NULL, 10);

  //int kill(pid_t pid, int sig);
  if (kill(pid, sig) < 0)
  {
    fprintf(stderr, "Send signal %d to process/process group %d failed: %s\n", sig, pid, strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Sent signal %d to process/process group %d successfully.\n", sig, pid);

  return 0;
}
