#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
  //uid_t getuid(void);
  //uid_t geteuid(void);
  fprintf(stdout, "Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
  fprintf(stdout, "Real GID: %d, Effective GID: %d\n", getgid(), getegid());

  return 0;
}
