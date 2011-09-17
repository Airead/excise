#include <unistd.h>		// close()
#include <stdio.h>		// fprintf()
#include <stdlib.h>		// exit()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>		// strerror()
#include <errno.h>		// errno

int main(int argc, char **argv)
{
  int fd;

  //------------------------------------------------------------------
  // flags parameter:
  //
  // 1) access mode: O_RDONLY, O_WRONLY, O_RDWR
  // 2) create flags: O_CREAT,O_EXCL,O_NOCTTY,and O_TRUNC
  // 3) status flags: O_APPEND, O_ASYNC, O_TRUNC, O_CLOEXEC, O_CREAT, O_DIRECT, O_DIRECTORY, O_EXCL, O_LARGEFILE, O_NOATIME, O_NOCTTY,  O_NONBLOCK or O_NDELAY, O_SYNC, O_TRUNC
  //------------------------------------------------------------------

  //int open(const char *pathname, int flags);
  fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL, 0777);

  // open()  and  creat()  return  the  new file descriptor, or -1 if an error
  // occurred (in which case, errno is set appropriately).
  if (fd < 0)
  {
    fprintf(stderr, "Open file %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open file %s successfully, fd = %d.\n", argv[1], fd);

  // int close(int fd);
  close(fd);

  return 0;
}
