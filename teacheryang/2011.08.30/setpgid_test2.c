#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t pid[10];
  int i;

  for (i = 0; i < 10; i++)
  {
    if ((pid[i] = fork()) < 0)
    {
      // failed
    }
    else if (pid[i] == 0)
    {
      // child process
      break;
    }
    else
    {
      // parent process
      fprintf(stdout, "[%d]Create a new child process %d.\n", getpid(), pid[i]);

      setpgid(pid[i], pid[0]);
    }
  }

  sleep(1000);

  return 0;
}
