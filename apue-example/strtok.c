/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 22:30:33 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strtok(char *str, const char *delim);
 * char *strtok_r(char *str, const char *delim, char **saveptr);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage: %s <strtok> <strtok_r>\n", argv[0]);
		exit(1);
	}

	char str1[] = "frhgfrhgfrhgfrhg";
	char str2[] = "frhgfrhgfrhgfrhg";
	char *p;
	int length;

	fprintf(stdout, "%s\n", str1);

	//char *strtok(char *str, const char *delim);
	p = strtok(str1, argv[1]);
	length = sizeof(str1);
	while(p != NULL && p < str1 + length ){
		fprintf(stdout, "strtok: %s\n", p);
		p = p + strlen(p) + 1;
		p = strtok(p, argv[1]);
	}
	//char *strtok_r(char *str, const char *delim, char **saveptr);
	
}
