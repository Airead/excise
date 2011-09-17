#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

void signal_handler(int signum);

int main(int argc, char **argv)
{
  int fd[2];

  //int pipe(int filedes[2]);
  if (pipe(fd) < 0)
  {
    fprintf(stderr, "[%d]Create pipe failed: %s\n", getpid(), strerror(errno));
    exit(1);
  }

  fprintf(stdout, "[%d]Created a new pipe, read end: %d, write end: %d\n", getpid(), fd[0], fd[1]);

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
    close(fd[1]);
    //exit(0);

    char buffer[BUFFER_SIZE];
    ssize_t n;

    for (;;)
    {
    read_again:
      //ssize_t read(int fd, void *buf, size_t count);
      if ((n = read(fd[0], buffer, sizeof(buffer) - 1)) < 0)
      {
	// error
	if (errno == EINTR)
	{
	  goto read_again;
	}
	else
	{
	  fprintf(stderr, "[%d]Read from pipe failed: %s\n", getpid(), strerror(errno));
	  break;
	}
      }
      else if (n == 0)
      {
	// write end closed
	fprintf(stdout, "[%d]Write end closed, exit.\n", getpid());

	close(fd[0]);
	break;
      }
      else
      {
	// success
	buffer[n] = '\0';
	fprintf(stdout, "[%d]Read %d bytes from pipe: %s\n", getpid(), n, buffer);
      }
    }

    exit(0);
  }
  else
  {
    // parent process
    close(fd[0]);

    signal(SIGPIPE, signal_handler);

    char *message = "How are you?";
    ssize_t n;

    //ssize_t write(int fd, const void *buf, size_t count);
    if ((n = write(fd[1], message, strlen(message))) < 0)
    {
      // error
      if (errno == EPIPE)
      {
	fprintf(stderr, "[%d]No readers.\n", getpid());
	// close write end.
      }
      else
      {
	fprintf(stdout, "[%d]Write data to pipe failed: %s\n", getpid(), strerror(errno));
      }
    }
    else
    {
      fprintf(stdout, "[%d]Write %d bytes to pipe.\n", getpid(), n);
    }

    close(fd[1]);
  }

  //pause();

  return 0;
}

void signal_handler(int signum)
{
  fprintf(stdout, "[%d]Caught signal %d.\n", getpid(), signum);
}
