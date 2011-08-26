/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 10:10:29 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int access(const char *pathname, int mode);
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	/* | mode | Description                 |
	 * | R_OK | test for read permission    |
	 * | W_OK | test for write permission   |
	 * | X_OK | test for execute permission |
	 * | F_OK | test for existence of file  |
	 */

	//step 1. print one file's permisson
	fprintf(stdout, "file %s:\n", argv[1]);

	//int access(const char *pathname, int mode)
	if(access(argv[1], F_OK) < 0){
		if(errno == EACCES){
		}else{
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(1);
		}
	}else{
		fprintf(stdout, "F_OK\n");
	}
	
	if(access(argv[1], R_OK) < 0){
		if(errno == EACCES){
		}else{
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(1);
		}
	}else{
		fprintf(stdout, "R_OK\n");
	}
	
	if(access(argv[1], W_OK) < 0){
		if(errno == EACCES){
		}else{
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(1);
		}
	}else{
		fprintf(stdout, "W_OK\n");
	}
	
	if(access(argv[1], X_OK) < 0){
		if(errno == EACCES){
		}else{
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(1);
		}
	}else{
		fprintf(stdout, "X_OK\n");
	}
	
	return 0;
}
