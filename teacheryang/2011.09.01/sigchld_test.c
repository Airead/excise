#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig);

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
    sleep(3);
    abort();
    exit(0);
  }
  else
  {
    // parent process
    signal(SIGCHLD, signal_handler);

    for (;;)
    {
      fprintf(stdout, ".");
      fflush(stdout);

      sleep(1);
    }
  }

  return 0;
}

void signal_handler(int sig)
{
  int errno_save = errno;

  fprintf(stdout, "Caught signal %d.\n", sig);

  pid_t terminated_pid;
  int status;

  //pid_t wait(int *status);
  if ((terminated_pid = wait(&status)) < 0)
  {
    fprintf(stderr, "wait() failed: %s\n", strerror(errno));
    exit(1);
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

  errno = errno_save;
}
