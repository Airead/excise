#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int global_value = 0;

int main(int argc, char **argv)
{
  pid_t pid;
  int local_value = 100;

  //pid_t vfork(void);
  if ((pid = vfork()) < 0)
  {
    // failed
  }
  else if (pid == 0)
  {
    // child process
    fprintf(stdout, "[%d]I'm child process, pid = %d, ppid = %d\n", getpid(), getpid(), getppid());

    global_value = 99;
    local_value = getpid();

    fprintf(stdout, "[%d]global_value = %d\n", getpid(), global_value);
    fprintf(stdout, "[%d]local_value = %d\n", getpid(), local_value);

    sleep(5);

    // WRONG: exit(0);
    _exit(0);
  }
  else
  {
    // parent process
    fprintf(stdout, "[%d]I'm parent process, pid = %d, ppid = %d, new created child process' pid = %d\n", getpid(), getpid(), getppid(), pid);

    fprintf(stdout, "[%d]global_value = %d\n", getpid(), global_value);
    fprintf(stdout, "[%d]local_value = %d\n", getpid(), local_value);
  }

  return 0;
}
