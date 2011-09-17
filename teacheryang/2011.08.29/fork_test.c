#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  pid_t pid;

  //pid_t fork(void);
  if ((pid = fork()) < 0)
  {
    //On failure, a -1 will be returned in the parent’s context, 
    //no child process will be created, and errno will be set 
    //appropriately.
    fprintf(stderr, "fork() failed: %s\n", strerror(errno));
    exit(1);
  }
  else if (pid == 0)
  {
    // child process
    // On success, a 0 is returned in the child’s thread of execution.   
    fprintf(stdout, "[%d]I'm child process, pid = %d, ppid = %d\n", getpid(), getpid(), getppid());
  }
  else
  {
    // parent process
    // On success, the PID of the child process is returned in the parent’s thread of execution, 
    fprintf(stdout, "[%d]I'm parent process, pid = %d, ppid = %d, new created process' pid = %d\n", getpid(), getpid(), getppid(), pid);
  }

  // common code for parent and child process
  fprintf(stdout, "[%d]I'm here.\n", getpid());

  sleep(1000);

  return 0;
}
