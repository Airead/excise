/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 20:50:39 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * size_t strspn(const char *s, const char *accept);
 * size_t strcspn(const char *s, const char *reject);
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
	
	char s[] = "The strspn function calculates the length of the initial"
		" segment of s which consists entirely of characters in accept.";
	size_t size;

	fprintf(stdout, "%s\n", s);

	//size_t strspn(const char *s, const char *accept);
	size = strspn(s, argv[1]);
	fprintf(stdout, "%u\n", (unsigned int)size);

	//size_t strcspn(const char *s, const char *reject);
	size = strcspn(s, argv[1]);
	fprintf(stdout, "%u\n", (unsigned int)size);

	return 0;
}
