#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  uid_t uid;

  uid = 500;

  fprintf(stdout, "Before setuid(%d), UID: %d, EUID: %d\n", uid, getuid(), geteuid());

  //int setuid(uid_t uid);
  if (setuid(uid) < 0)
  {
    fprintf(stderr, "setuid() failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "After setuid(%d), UID: %d, EUID: %d\n", uid, getuid(), geteuid());

  uid = 99;

  //int setuid(uid_t uid);
  if (setuid(uid) < 0)
  {
    fprintf(stderr, "setuid() failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "After setuid(%d), UID: %d, EUID: %d\n", uid, getuid(), geteuid());

  return 0;
}
