/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 25 13:43:01 CST			*
 ********************************************************
 *		after studying C 38 days		*
 *		after studying APUE 3 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int stat(const char *path, struct stat *buf);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat s;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	//int lstat(const char *path, struct stat *buf)
	if((lstat(argv[1], &s)) < 0){
		fprintf(stderr, "get file info error %s\n", strerror(errno));
		exit(1);			
	}

#if 0

	struct stat {
		dev_t     st_dev;     /* ID of device containing file */
		ino_t     st_ino;     /* inode number */
		mode_t    st_mode;    /* protection */
		nlink_t   st_nlink;   /* number of hard links */
		uid_t     st_uid;     /* user ID of owner */
		gid_t     st_gid;     /* group ID of owner */
		dev_t     st_rdev;    /* device ID (if special file) */
		off_t     st_size;    /* total size, in bytes */
		blksize_t st_blksize; /* blocksize for file system I/O */
		blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
		time_t    st_atime;   /* time of last access */
		time_t    st_mtime;   /* time of last modification */
		time_t    st_ctime;   /* time of last status change */
	};

#endif
	/* print all info without formating */
	fprintf(stdout, " File: '%s'\n", argv[1]);

	fprintf(stdout, " device contating file is %lu\n", 
		(unsigned long int)s.st_dev);

	fprintf(stdout, " inode number is %lu\n", 
		(unsigned long int)s.st_ino);

	fprintf(stdout, "protection is %#o\n", 
		(unsigned int)s.st_mode);

	fprintf(stdout, "number of hard link is %u\n", 
		(unsigned int)s.st_nlink);

	fprintf(stdout, "user ID of owner is %u\n", 
		(unsigned int)s.st_uid);

	fprintf(stdout, "group ID of owner is %u\n", 
		(unsigned int)s.st_gid);

	fprintf(stdout, "device ID is %u\n", 
		(unsigned int)s.st_rdev);

	fprintf(stdout, "total size is %u bytes\n", 
		(unsigned int)s.st_size);

	fprintf(stdout, "blocksize for file system I/O is %u\n", 
		(unsigned int)s.st_blksize);

	fprintf(stdout, "number of %u block allocated\n", 
		(unsigned int)s.st_blocks);

	fprintf(stdout, "time of last access is %ld\n", (long int)s.st_atime);

	fprintf(stdout, "time of last modification is %ld\n", 
		(long int)s.st_mtime);

	fprintf(stdout, "time of last status change is %ld\n", 
		(long int)s.st_ctime);

	return 0;
}
