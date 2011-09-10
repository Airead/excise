/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 27 17:24:35 CST			*
 ********************************************************
 *		after studying C 40 days		*
 *		after studying APUE 5 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * how to change decimal to octal
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <decimal long int>\n", argv[0]);
		exit(1);
	}
	
	long int l;

	//long int strtol(const char *nptr, char **endptr, int base);
	l = strtol(argv[1], NULL, 10);

	fprintf(stdout, "%#lo\n", l);
	
	return 0;
}
