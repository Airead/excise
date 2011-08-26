/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 16:25:44 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * how to get times of file
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void print_time(time_t time);

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	/* struct stat {
	 * 	dev_t     st_dev;     ID of device containing file
	 * 	ino_t     st_ino;     inode number
	 * 	mode_t    st_mode;    protection
	 * 	nlink_t   st_nlink;   number of hard links
	 * 	uid_t     st_uid;     user ID of owner
	 * 	gid_t     st_gid;     group ID of owner
	 * 	dev_t     st_rdev;    device ID (if special file)
	 * 	off_t     st_size;    total size, in bytes
	 * 	blksize_t st_blksize; blocksize for file system I/O
	 * 	blkcnt_t  st_blocks;  number of 512B blocks allocated
	 * 	time_t    st_atime;   time of last access
	 * 	time_t    st_mtime;   time of last modification
	 * 	time_t    st_ctime;   time of last status change
	 * };
	 */

	struct stat s;
	//int stat(const char *path, struct stat *buf);
	if(stat(argv[1], &s) < 0){
		fprintf(stderr, "get %s status failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "get %s status success\n", argv[1]);
	}

	/* print times of file */
	fprintf(stdout, "%s:\n", argv[1]);

	fprintf(stdout, "last access time: ");
	print_time(s.st_atime);

	fprintf(stdout, "last modification time: ");
	print_time(s.st_mtime);

	fprintf(stdout, "last status chage time: ");
	print_time(s.st_ctime);

	return 0;
}

/*
 * print time with format
 */
void print_time(time_t time)
{
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
	struct tm *t;
	
	//struct tm *localtime(const time_t *timep)
	if((t = localtime(&time)) == NULL){
		fprintf(stderr, "locate time failed: %s\n", strerror(errno));
		exit(1);
	}
	
	fprintf(stdout, "%4d-%02d-%02d %02d:%02d\n",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);	
}
