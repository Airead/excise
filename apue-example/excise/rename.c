/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 15:22:02 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int rename(const char *oldpath, const char *newpath);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <oldpath> <newpath>\n", argv[0]);
		exit(1);
	}

	//int rename(const char *oldpath, const char *newpath);
	if(rename(argv[1], argv[2]) < 0){
		fprintf(stderr, "rename `%s' to `%s' failed: %s\n", argv[1], argv[2], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout,  "rename `%s' to `%s' success \n", argv[1], argv[2]);
	}
	
	return 0;
}
