/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 24 09:54:16 CST			*
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

/*
 * This program can create a file
 * if file exist, O_TRUNC it
 * if not, create it
 */
int main(int argc, char *argv[])
{
	int fd;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC)) < 0){
		perror("create file error: ");
	}else{
		fprintf(stdout, "create %s success\n", argv[1]);
	}

	return 0;
}
