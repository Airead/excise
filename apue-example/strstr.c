/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 22:01:08 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strstr(const char *haystack, const char *needle);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <str>\n", argv[0]);
		exit(1);
	}
	
	char haystack[] = "The strstr() function finds the first occurrence of"
		" the substring needle in the string haystack.  The terminating"
		" '\\0' characters are not compared.";

	fprintf(stdout, "%s\n\n", haystack);

	//char *strstr(const char *haystack, const char *needle);
	fprintf(stdout, "%s\n", strstr(haystack, argv[1]));
	
	return 0;
}
