/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 16:03:09 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * print process args and environment
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
	char **p;
	int i;

	/* print args */
	p = argv; i = 0;
	while(*p != NULL){
		fprintf(stdout, "[%d]%s\n", i++, *p++);
	}

	extern char **environ;
	
	/* print environment */
	p = environ;
	while(*p != NULL && p != NULL){
		fprintf(stdout, "%s\n", *p++);
	}

	return 0;
}
