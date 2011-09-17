#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
#if 0
  int setpgid(pid_t pid, pid_t pgid);
  pid_t getpgid(pid_t pid);
  int setpgrp(void);
  pid_t getpgrp(void);
#endif

  //fprintf(stdout, "PGID: %d\n", getpgrp());
  //fprintf(stdout, "PGID: %d\n", getpgid(getpid()));
  fprintf(stdout, "[%d]PGID: %d\n", getpid(), getpgid(0));

  pid_t pid;

  //pid_t fork(void);
  if ((pid = fork()) < 0)
  {
    // failed
    fprintf(stderr, "fork() failed: %s\n", strerror(errno));
    exit(1);
  }
  else if (pid == 0)
  {
    // child process
    fprintf(stdout, "[%d]Before setpgid(0,0), PGID: %d\n", getpid(), getpgid(0));

    //int setpgid(pid_t pid, pid_t pgid);
    //setpgid(0, 0);
    sleep(5);

    fprintf(stdout, "[%d]After setpgid(0,0), PGID: %d\n", getpid(), getpgid(0));
  }
  else
  {
    // parent process
    fprintf(stdout, "[%d]PGID: %d\n", getpid(), getpgid(0));

    //setpgid(pid, pid);
    setpgid(pid, 0);
  }

  sleep(1000);

  return 0;
}
