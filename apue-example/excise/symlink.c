/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 15:54:57 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int symlink(const char *oldpath, const char *newpath);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage: %s <oldpath> <newpath>\n", argv[0]);
		exit(1);
	}

	//int symlink(const char *oldpath, const char *newpath);
	if(symlink(argv[1], argv[2]) < 0){
		fprintf(stderr, "create %s -> %s failed: %s\n", argv[2], argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "create %s -> %s success\n", argv[2], argv[1]);
	}

	return 0;
}
