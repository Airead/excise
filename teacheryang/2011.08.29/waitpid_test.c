#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
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
    //abort();

    sleep(1000);

    exit(0);
  }
  else
  {
    // parent process

    pid_t terminated_pid;
    int status;
    int options = 0;

    options |= WNOHANG;

    for (;;)
    {
      //pid_t wait(int *status);
      //pid_t waitpid(pid_t pid, int *status, int options);
      if ((terminated_pid = waitpid(-1, &status, options)) < 0)
      {
	fprintf(stderr, "waitpid() failed: %s\n", strerror(errno));
        break;
	//exit(1);
      }
      else if (terminated_pid == 0)
      {
	// if WNOHANG was specified and no child(ren) specified  by  pid  has  yet changed state, then 0 is returned.
	fprintf(stdout, "[%d]No child terminated\n", getpid());
      }
      else
      {
	fprintf(stdout, "[%d]Child process %d terminated, status = 0x%08x, ", getpid(), terminated_pid, status);

	if (WIFEXITED(status))
	{
	  fprintf(stdout, "normal terminated, status code = %d\n", WEXITSTATUS(status));
	}
	else
	{
	  fprintf(stdout, "abnormal terminated, ");

	  if (WIFSIGNALED(status))
	  {
	    fprintf(stdout, "by signal %d, ", WTERMSIG(status));

	    if (WCOREDUMP(status))
	    {
	      fprintf(stdout, "core dumped.");
	    }
	  }

	  fprintf(stdout, "\n");
	}
      }

      sleep(1);
    }
  }

  return 0;
}
