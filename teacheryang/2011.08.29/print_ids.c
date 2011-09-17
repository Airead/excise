#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  //pid_t getpid(void);
  //pid_t getppid(void);
  fprintf(stdout, "PID: %d, PPID: %d\n", getpid(), getppid());

  //uid_t getuid(void);
  //uid_t geteuid(void);
  fprintf(stdout, "Real UID: %d, Effective UID: %d\n", getuid(), geteuid());

  //gid_t getgid(void);
  //gid_t getegid(void);

  fprintf(stdout, "Real GID: %d, Effective GID: %d\n", getgid(), getegid());

  //pid_t getpgid(pid_t pid);
  fprintf(stdout, "PGID: %d\n", getpgid(0));

  //pid_t getsid(pid_t pid);
  fprintf(stdout, "SID: %d\n", getsid(0));

  // No method to get saved set-user-id value
  // No method to saved set-group-id value

  // Get list of supplementary group IDs
  //int getgroups(int size, gid_t list[]);

  sleep(1000);

  return 0;
}
