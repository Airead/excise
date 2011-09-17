#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDONLY)) < 0)
  {
    fprintf(stderr, "Open file %s for reading failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  off_t offset;

  //Upon successful completion, lseek() returns the resulting offset location
  //as measured in bytes from the beginning of the file.  Otherwise, a  value
  //of (off_t) -1 is returned and errno is set to indicate the error.

  //off_t lseek(int fd, off_t offset, int whence);
  if ((offset = lseek(fd, 100, SEEK_SET)) == (off_t) - 1)
  {
    fprintf(stderr, "Reposition file offset failed: %s\n", strerror(errno));
  }

  fprintf(stdout, "New file offset is %d\n", (int)offset);

  time_t value;

  //ssize_t read(int fd, void *buf, size_t count);
  read(fd, &value, sizeof(value));

  struct tm *tm;

  //struct tm *localtime(const time_t *timep);
  tm = localtime(&value);

#if 0
struct tm {
               int tm_sec;         /* seconds */
               int tm_min;         /* minutes */
               int tm_hour;        /* hours */
               int tm_mday;        /* day of the month */
               int tm_mon;         /* month */
               int tm_year;        /* year */
               int tm_wday;        /* day of the week */
               int tm_yday;        /* day in the year */
               int tm_isdst;       /* daylight saving time */
           };
#endif

  fprintf(stdout, "Time: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
  
  char message[1024];

  //off_t lseek(int fd, off_t offset, int whence);
  lseek(fd, 200, SEEK_SET);

  memset(message, 0, sizeof(message));

  read(fd, message, sizeof(message));

  fprintf(stdout, "Message: %s\n", message);

  close(fd);

  return 0;
}
