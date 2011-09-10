/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 15:57:30 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * void exit(int status);
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <functionname: exit | _exit | _Exit\n", argv[0]);
		exit(1);
	}

	fprintf(stdout, "Hello World!");

	//int strcmp(const char *s1, const char *s2);
	if(strcmp(argv[1], "exit") == 0){
		exit(0);
	}else if(strcmp(argv[1], "_exit") == 0){
		_exit(0);
	}else if(strcmp(argv[1], "_Exit") == 0){
		_Exit(0);
	}

	return 0;
}
