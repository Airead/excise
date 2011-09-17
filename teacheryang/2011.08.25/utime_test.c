#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <utime.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  struct tm t;

  // 1998-7-19 20:45:21

#if 0
  struct tm
  {
    int tm_sec;			/* seconds */
    int tm_min;			/* minutes */
    int tm_hour;		/* hours */
    int tm_mday;		/* day of the month */
    int tm_mon;			/* month */
    int tm_year;		/* year */
    int tm_wday;		/* day of the week */
    int tm_yday;		/* day in the year */
    int tm_isdst;		/* daylight saving time */
  };
#endif

  t.tm_year = 1998 - 1900;
  t.tm_mon = 7 - 1;
  t.tm_mday = 19;
  t.tm_hour = 20;
  t.tm_min = 45;
  t.tm_sec = 21;

  struct utimbuf utb;

  // time_t mktime(struct tm *tm);
  utb.actime = mktime(&t);
  utb.modtime = mktime(&t);

#if 0
  struct utimbuf
  {
    time_t actime;		/* access time */
    time_t modtime;		/* modification time */
  };
#endif

  //int utime(const char *filename, const struct utimbuf *buf);
  if (utime(argv[1], &utb) < 0)
  {
    fprintf(stderr, "Change timestamp of file %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Timestamp of file %s changed.\n", argv[1]);
  return 0;
}
