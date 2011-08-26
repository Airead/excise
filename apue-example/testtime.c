/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 24 23:09:04 CST			*
 ********************************************************
 *		after studying C 37 days		*
 *		after studying APUE 2 days		*
 ********************************************************/

#include <stdio.h>
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
	struct stat s;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	//int stat(const char *path, struct stat *buf);
	if(lstat(argv[1], &s) < 0){
		fprintf(stderr, "get file info error %s\n", strerror(errno));
		exit(1);
	}
	
	fprintf(stdout, "time = %ld\n", (long int)s.st_atime);
}
