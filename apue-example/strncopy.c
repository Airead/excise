/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 28 09:52:25 CST			*
 ********************************************************
 *		after studying C 41 days		*
 *		after studying APUE 6 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strncpy(char *dest, const char *src, size_t n);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char src[10] = "src";
	char dest[10]; "dest";

	//char *strncpy(char *dest, const char *src, size_t n);
	/* test size_t is a negative */
	//!strncpy(dest, src, -1); 

	/* test '\0' at end */
	strncpy(dest, "0123456789", 10);
	fprintf(stdout, "%s\n", dest); /* result: non '\0' */
	
	return 0;
}
