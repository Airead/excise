#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void dump_flags(int flags);

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDONLY | O_CREAT | O_EXCL, 0644)) < 0)
  {
    // failed
    fprintf(stderr, "Open file %s for reading failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  int newfd;

  newfd = fcntl(fd, F_DUPFD, 9);

  int flags;

  //------------------------------------------------------------------
  // Get original flags
  //------------------------------------------------------------------
  flags = fcntl(fd, F_GETFL);
  fprintf(stdout, "Before change status: \n");
  dump_flags(flags);

  int newfd_flags;

  newfd_flags = fcntl(newfd, F_GETFL);
  fprintf(stdout, "Before change status of fd, newfd's flags: \n");
  dump_flags(newfd_flags);

  //------------------------------------------------------------------
  // Modify flags on orignal value
  //------------------------------------------------------------------
  // On Linux this command can only change the 
  // O_APPEND, O_ASYNC, O_DIRECT, O_NOATIME,
  // and O_NONBLOCK flags.

  flags |= O_APPEND;		// enable O_APPEND flag
  //flags &= ~O_APPEND; // disable O_APPEND flag

  //------------------------------------------------------------------
  // Set new flags to file descriptor
  //------------------------------------------------------------------
  // int fcntl(int fd, int cmd, ... /* arg */ );
  if (fcntl(fd, F_SETFL, flags) < 0)
  {
    fprintf(stderr, "Change file status flags failed: %s\n", strerror(errno));
    exit(1);
  }

  flags = fcntl(fd, F_GETFL);
  fprintf(stdout, "After change status: \n");
  dump_flags(flags);

  newfd_flags = fcntl(newfd, F_GETFL);
  fprintf(stdout, "After change status of fd, newfd's flags: \n");
  dump_flags(newfd_flags);

  close(fd);

  return 0;
}

void dump_flags(int flags)
{
  // access mode: O_RDONLY, O_WRONLY, O_RDWR
  int access_mode;

  // defined in file /usr/include/asm-generic/fcntl.h
#if 0
#  define O_ACCMODE	00000003
#  define O_RDONLY	00000000
#  define O_WRONLY	00000001
#  define O_RDWR		00000002
#endif

  access_mode = flags & O_ACCMODE;

  switch (access_mode)
  {
    case O_RDONLY:
      fprintf(stdout, "read only");
      break;
    case O_WRONLY:
      fprintf(stdout, "write only");
      break;
    case O_RDWR:
      fprintf(stdout, "r/w");
      break;
  }

  // creation flags: O_CREAT, O_EXCL, O_NOCTTY, and O_TRUNC
  if (flags & O_CREAT)
  {
    fprintf(stdout, " O_CREAT");
  }

  if (flags & O_EXCL)
  {
    fprintf(stdout, " O_EXCL");
  }

  if (flags & O_NOCTTY)
  {
    fprintf(stdout, " O_NOCTTY");
  }

  if (flags & O_TRUNC)
  {
    fprintf(stdout, " O_TRUNC");
  }

  // status flags: O_APPEND, O_ASYNC, O_TRUNC, O_CLOEXEC, O_CREAT, O_DIRECT, O_DIRECTORY, O_EXCL, O_LARGEFILE, O_NOATIME, O_NOCTTY,  O_NONBLOCK or O_NDELAY, O_SYNC, O_TRUNC
  if (flags & O_APPEND)
  {
    fprintf(stdout, " O_APPEND");
  }

  if (flags & O_ASYNC)
  {
    fprintf(stdout, " O_ASYNC");
  }

  if (flags & O_NONBLOCK)
  {
    fprintf(stdout, " O_NONBLOCK");
  }

  fprintf(stdout, "\n");
}
