#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int sig;

  pid = (pid_t) strtol(argv[1], NULL, 10);
  sig = (int) strtol(argv[2], NULL, 10);

#if 0
  union sigval
  {
    int sival_int;
    void *sival_ptr;
  };
#endif

  union sigval si;

  si.sival_int = (int) strtol(argv[3], NULL, 10);

  //int sigqueue(pid_t pid, int sig, const union sigval value);
  if (sigqueue(pid, sig, si) < 0)
  {
    fprintf(stderr, "Send signal %d with data %d to process %d failed: %s\n", sig, si.sival_int, pid, strerror(errno));
    exit(1);
  }

  fprintf(stdout, "[%d]Sent signal %d with data %d to process %d successfully\n", getpid(), sig, si.sival_int, pid);

  return 0;
}
