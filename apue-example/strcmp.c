/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 20:15:46 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int strcmp(const char *s1, const char *s2);
 * int strncmp(const char *s1, const char *s2, size_t n);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char str1[] = "flnrenhao";
	char str2[] = "flwenfeng";

	fprintf(stdout, "str1: %s\nstr2: %s\n", str1, str2);
	
	//int strcmp(const char *s1, const char *s2);
	fprintf(stdout, "strcmp result: %d\n", strcmp(str1, str2));

	//int strncmp(const char *s1, const char *s2, size_t n);
	fprintf(stdout, "strcmp result: %d\n", strncmp(str1, str2, 2));

	//!fprintf(stdout, "strcmp NULL: %d\n", strcmp(NULL, str1));  SIGSEGV error

	return 0;
}
