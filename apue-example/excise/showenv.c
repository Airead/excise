/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 19:54:20 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * show all environment variable
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int main(int argc, char *argv[])
{
	char **env = environ;

	env = environ;
	while(*env != NULL){
		fprintf(stdout, "%s\n", *env++);
	}
	
	return 0;
}
