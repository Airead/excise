#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig);

int main(int argc, char **argv)
{
  int fd[2];

  //int pipe(int filedes[2]);
  if (pipe(fd) < 0)
  {
    fprintf(stderr, "Create pipe failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "[%d]Create a new pipe, read end is %d, write end is %d.\n", getpid(), fd[0], fd[1]);

  //sleep(1000);

  pid_t pid;

  //pid_t fork(void);
  if ((pid = fork()) < 0)
  {
    // failed
    fprintf(stderr, "fork() failed: %s\n", strerror(errno));

    close(fd[0]);
    close(fd[1]);

    exit(1);
  }
  else if (pid == 0)
  {
    // child process
    close(fd[0]);		// close read end

    signal(SIGPIPE, signal_handler);

    //sleep(1000);
    sleep(3);

    ssize_t n;

    //ssize_t write(int fd, const void *buf, size_t count);
    if ((n = write(fd[1], "x", 1)) < 0)
    {
      if (errno == EPIPE)
      {
	fprintf(stderr, "[%d]Read end closed, give up.\n", getpid());
	exit(1);
      }
    }

    exit(0);
  }
  else
  {
    // parent process
    close(fd[1]);		// close write end
    close(fd[0]);		// close read end

    //sleep(1000);

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
  }

  close(fd[0]);
  close(fd[1]);

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stdout, "[%d]Caught signal %d.\n", getpid(), sig);
}
