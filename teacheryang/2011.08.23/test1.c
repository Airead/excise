#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void dump_flags(int flags);

int main(int argc, char **argv)
{
  int flags;

  //int fcntl(int fd, int cmd, ... /* arg */ );
  flags = fcntl(0, F_GETFL);
  //fprintf(stdout, "0: 0x%08x\n", flags);
  fprintf(stdout, "stdin : ");
  dump_flags(flags);

  //int fcntl(int fd, int cmd, ... /* arg */ );
  flags = fcntl(1, F_GETFL);
  //fprintf(stdout, "1: 0x%08x\n", flags);
  fprintf(stdout, "stdout: ");
  dump_flags(flags);

  //int fcntl(int fd, int cmd, ... /* arg */ );
  flags = fcntl(2, F_GETFL);
  //fprintf(stdout, "2: 0x%08x\n", flags);
  fprintf(stdout, "stderr: ");
  dump_flags(flags);

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
