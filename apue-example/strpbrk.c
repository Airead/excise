/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 21:52:14 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * char *strpbrk(const char *s, const char *accept);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <accept_str>\n", argv[0]);
		exit(1);
	}

	char s[] = "The  strpbrk()  function  locates  the  first  occurrence in"
		"the string s of any of the characters in the string accept.";
	char *p;

	fprintf(stdout, "%s\n\n", s);

	//char *strpbrk(const char *s, const char *accept);
	if((p = strpbrk(s, argv[1])) == NULL){
		fprintf(stdout, "cannot match anything\n");
	}else{
		fprintf(stdout, "%s\n", p);
	}

	return 0;
}
