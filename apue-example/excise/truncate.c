/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 14:33:57 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int truncate(const char *path, off_t length);
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage: %s <filename> <numbytes>\n", argv[1]);
		exit(1);
	}
	
	off_t offset;

	//long int strtol(const char *nptr, char **endptr, int base);
	offset = (off_t)strtol(argv[2], NULL, 10);

	//int truncate(const char *path, off_t length);
	if(truncate(argv[1], offset) < 0){
		fprintf(stderr, "truncate %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "truncate %s success\n", argv[1]);
	}
	
	return 0;
}
