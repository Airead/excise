#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t pid[10];
  int i;

  int parent_flag = 1;

  for (i = 0; i < 10; i++)
  {
    if ((pid[i] = fork()) < 0)
    {
      // failed
    }
    else if (pid[i] == 0)
    {
      // child process
      parent_flag = 0;

      for (;;)
      {
	fprintf(stdout, "%d", i);
	fflush(stdout);

	sleep(1);
      }

      exit(0);
      //break;
    }
    else
    {
      // parent process
      fprintf(stdout, "[%d]Create a new child process %d.\n", getpid(), pid[i]);

      //setpgid(pid[i], pid[0]);
    }
  }

  if (parent_flag > 0)
  {
    // do something here.
    setpgid(pid[0], pid[0]);

    for (i = 1; i < 10; i++)
    {
      setpgid(pid[i], pid[0]);
    }
  }

  sleep(1000);

  return 0;
}
