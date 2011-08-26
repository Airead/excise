/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 20:01:05 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strchr(const char *s, int c);
 * char *strrchr(const char *s, int c);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(void)
{
	char dest[BUFSIZE] = "frhfrhfrhfrh";
	char *p;
	
	fprintf(stdout, "dest: %s\n", dest);
	
	//char *strchr(const char *s, int c);
	fprintf(stdout, "strchr result: %s\n", strchr(dest, 'r'));

	//char *strrchr(const char *s, int c);
	fprintf(stdout, "strrchr result: %s\n", strrchr(dest, 'r'));

	return 0;

}
