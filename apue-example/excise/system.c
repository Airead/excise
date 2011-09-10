/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 17:17:02 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int system(const char *command);
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
	char buf[1024];
	char **p;

	//void *memset(void *s, int c, size_t n);
	memset(buf, 0, sizeof(buf));
	       
	//strncpy(buf, "./printallargv ", sizeof(buf) - 1);
	strncpy(buf, "./printallargv", sizeof(buf) - 1); // WRONG!

	p = argv + 1;
	while(*p != NULL){
		//char *strncat(char *dest, const char *src, size_t n);
		strncat(buf, *p++, sizeof(buf) - strlen(buf) - 2);
		strncat(buf, " ", 1);
	}
	

	fprintf(stdout, "%s\n", buf);
	       
	//int system(const char *command);
	if(system(buf) < 0){
		perror("system failed");
		exit(1);
	}

	return 0;
}
