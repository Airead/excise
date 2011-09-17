#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define MAPPED_LENGTH	1024

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

  fprintf(stdout, "Open file %s for reading successfully.\n", argv[1]);

  void *addr;

  // On  success,  mmap() returns a pointer to the mapped area.  On error, the
  // value MAP_FAILED (that is, (void *) -1) is returned,  and  errno  is  set
  // appropriately.

  //void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  if ((addr = mmap(NULL, MAPPED_LENGTH, PROT_READ , MAP_SHARED, fd, 0)) == MAP_FAILED)
  {
    fprintf(stderr, "Map failed: %s\n", strerror(errno));
    close(fd);
    exit(1);
  }

  fprintf(stdout, "Map success, address: 0x%08x\n", (int) addr);

  for (;;)
  {
    time_t t;

    t = *((time_t *) (addr + 100));

    struct tm *tm;

    //struct tm *localtime(const time_t *timep);
    tm = localtime(&t);

#if 0
    struct tm
    {
      int tm_sec;		/* seconds */
      int tm_min;		/* minutes */
      int tm_hour;		/* hours */
      int tm_mday;		/* day of the month */
      int tm_mon;		/* month */
      int tm_year;		/* year */
      int tm_wday;		/* day of the week */
      int tm_yday;		/* day in the year */
      int tm_isdst;		/* daylight saving time */
    };
#endif

    fprintf(stdout, "Time: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

    fprintf(stdout, "Message: %s\n", (char *) (addr + 200));

    sleep(1);
  }

  //int munmap(void *addr, size_t length);
  if (munmap(addr, MAPPED_LENGTH) < 0)
  {
    fprintf(stderr, "Unmap failed: %s\n", strerror(errno));
    close(fd);
    exit(1);
  }

  close(fd);

  return 0;
}
