/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 16:58:59 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates functioin
 * int utime(const char *filename, const struct utimbuf *times);
 */

#include <stdio.h>
#include <utime.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	/* struct tm {
         *        int tm_sec;         seconds
         *        int tm_min;         minutes
         *        int tm_hour;        hours
         *        int tm_mday;        day of the month
         *        int tm_mon;         month
         *        int tm_year;        year
         *        int tm_wday;        day of the week
         *        int tm_yday;        day in the year
         *        int tm_isdst;       daylight saving time
	 *    };
	 */	
	struct tm t;
	
	t.tm_year = 2012 - 1900;
	t.tm_mon = 12 - 1;
	t.tm_mday = 21;
	t.tm_hour = 23;
	t.tm_min = 59;
	t.tm_sec = 59;
	t.tm_isdst = -1;

	time_t time;

	//time_t mktime(struct tm *tm);
	time = mktime(&t);

	/* struct utimbuf {
	 * 	time_t actime;       access time
	 * 	time_t modtime;      modification time
	 * };
	 */
	struct utimbuf tb;
	
	tb.actime = time;
	tb.modtime = time;

	//int utime(const char *filename, const struct utimbuf *times);
	if(utime(argv[1], &tb) < 0){
		fprintf(stderr, "utime %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "utime %s success\n", argv[1]);
	}

	return 0;
}
