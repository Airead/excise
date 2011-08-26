/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 10:44:06 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This pragram demonstrates function
 * mode_t umask(mode_t mask);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage : %s <filename> <umask>\n", argv[0]);
		exit(1);
	}

	//step 1. set process umask
	mode_t mask;
	
	//long int strtol(const char *nptr, char **endptr, int base)
	mask = (mode_t)strtol(argv[2], NULL, 8);
	fprintf(stdout, "mask = %#lo\n", (unsigned long int)mask);
	
	//mode_t umask(mode_t mask);
	umask(mask);
	
	//step 2. create a file, if exist, overwrite!
	int fd;

	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC), 0777) < 0){
		fprintf(stderr, "create %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "create %s success\n", argv[1]);
	}

	//step 3. close file
	close(fd);

	return 0;
}
