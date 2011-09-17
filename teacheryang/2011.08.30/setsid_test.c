#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //pid_t getsid(pid_t pid);
  fprintf(stdout, "SID: %d\n", getsid(0));

  pid_t pid;

  //pid_t fork(void);
  if ((pid = fork()) < 0)
  {
    // failed
  }
  else if (pid > 0)
  {
    // parent process, termination
    exit(0);
  }

  // child continue, make sure the child will be not process group leader

  //pid_t setsid(void);
  if (setsid() < 0)
  {
    fprintf(stderr, "setsid() failed: %s\n", strerror(errno));
    exit(1);
  }

  //pid_t getsid(pid_t pid);
  fprintf(stdout, "SID: %d\n", getsid(0));

  sleep(1000);

  return 0;
}
