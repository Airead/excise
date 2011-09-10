/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 12:08:41 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int execlp(const char *file, const char *arg, ...);
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
		fprintf(stderr, "usage: %s <elfname> [arg...]\n", argv[0]);
		exit(1);
	}else if(argc > 100){
		fprintf(stderr, "args numbers should less than 100\n");
		exit(1);
	}
	
	char *arg[100];
	char **p;

	//void *memset(void *s, int c, size_t n);
	memset(arg, 0, sizeof(arg));

	/* initial args */

	/* XXX: it's a bad idea to change value of argv */
	p = arg; argv++;	
	while(*argv != NULL){
		*p++ = *argv++;
	}
	*p = NULL;

	p = arg;
	while(*p != NULL){
		fprintf(stdout, "%s\n", *p++);
	}
	
	//int execv(const char *path, char *const argv[]);
	if(execv(*arg, arg) < 0){
		fprintf(stderr, "execv %s failed: %s\n", *arg, 
			strerror(errno));
		exit(1);
	}

	return 0;
}
