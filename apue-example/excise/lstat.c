/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 25 21:20:16 CST			*
 ********************************************************
 *		after studying C 38 days		*
 *		after studying APUE 3 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int lstat(const char *path, struct stat *buf);
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	//step 1. get file status
	struct stat s;

	//int lstat(const char *path, struct stat *buf);
	if(lstat(argv[1], &s) < 0){
		fprintf(stderr, "get %s status failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	//step 2. print all information without formating
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
       
