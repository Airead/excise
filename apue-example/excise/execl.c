/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 11:56:52 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int execl(const char *path, const char *arg, ...);
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
	if(argc < 2){
		fprintf(stderr, "usage: %s <elfname>\n", argv[0]);
		exit(1);
	}
	
	//int execl(const char *path, const char *arg, ...);
	if(execl(argv[1], argv[1], "-l", NULL) < 0){
		fprintf(stdout, "execl %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	return 0;
}
