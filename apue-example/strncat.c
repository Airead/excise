/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 19:30:30 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strncat(char *dest, const char *src, size_t n);
 * char *strncpy(char *dest, const char *src, size_t n);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 5

int main(int argc, char *argv[])
{
	char src[BUFSIZE];
	char dest[BUFSIZE];
	int size;

	if(argc < 3){
		fprintf(stderr, "usage: %s <src_str> <dest_str>\n", argv[0]);
		exit(1);
	}
	
	//void *memset(void *s, int c, size_t n);
	memset(src, 0, BUFSIZE);
	memset(dest, 0, BUFSIZE);

	//char *strncpy(char *dest, const char *src, size_t n);
	strncpy(src, argv[1], BUFSIZE - 1);
	strncpy(dest, argv[2], BUFSIZE - 1);

	fprintf(stdout, "src string: %s\n", src);
	fprintf(stdout, "dest string: %s\n", dest);

	size = BUFSIZE - 1 - strlen(dest);
	//char *strncat(char *dest, const char *src, size_t n);
	//!strncat(dest, src, -1); in fact, -1 is 0xffffffff(INT_MAX)
	strncat(dest, src, size);
	
	fprintf(stdout, "src string: %s\n", src);
	fprintf(stdout, "dest string: %s\n", dest);

	return 0;
}

