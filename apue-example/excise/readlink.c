/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 16:11:06 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * ssize_t readlink(const char *path, char *buf, size_t bufsiz);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 100

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	ssize_t readbytes;
	char buf[BUFSIZE];
	
	//void *memset(void *s, int c, size_t n);
	memset(buf, 0, sizeof(buf));
	
	//ssize_t readlink(const char *path, char *buf, size_t bufsiz);
	if((readbytes = readlink(argv[1], buf, BUFSIZE - 1)) < 0){
		fprintf(stderr, "readlink %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		buf[readbytes] = '\0';
		fprintf(stdout, "read %d bytes: %s\n", readbytes, buf);
	}

	return 0;
}
