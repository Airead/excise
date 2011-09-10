/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 16:31:35 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int atexit(void (*function)(void));
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void fun1(void)
{
	fprintf(stdout, "before exit 1\n");
}

void fun2(void)
{
	fprintf(stdout, "before exit 2\n");
}

int main(int argc, char *argv[]){

	fprintf(stdout,"system support at least %ld exit handlers\n", sysconf(_SC_ATEXIT_MAX));

	//int atexit(void (*function)(void));
	if(atexit(fun1) > 0){
		fprintf(stderr, "set atexit failed: %s", strerror(errno));
		exit(1);
	}

	if(atexit(fun1) > 0){
		fprintf(stderr, "set atexit failed: %s", strerror(errno));
		exit(1);
	}

	if(atexit(fun2) > 0){
		fprintf(stderr, "set atexit failed: %s", strerror(errno));
		exit(1);
	}

	//_exit(0); //test it!
	exit(0);
}
