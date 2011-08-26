/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 13:47:39 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int fchmod(int fd, mode_t mode);
 */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage: %s <filename> <mode_t>\n", argv[0]);
		exit(1);
	}
	
	int fd;

	//int open(const char *pathname, int flags);
	if((fd = open(argv[1], O_RDONLY)) < 0){
		fprintf(stderr, "open %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	mode_t mode;
	
	// long int strtol(const char *nptr, char **endptr, int base);
	mode = (mode_t)strtol(argv[2], NULL, 8);

	//int fchmod(int fd, mode_t mode);
	if(fchmod(fd, mode) < 0){
		fprintf(stderr, "change %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "change %s mode to %#lo\n", argv[1], (unsigned long int)mode);
	}

	close(fd);

	return 0;
}
