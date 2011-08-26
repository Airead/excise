/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 11:25:14 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * long int strtol(const char *nptr, char **endptr, int base);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage: %s <numstr> <base>\n", argv[0]);
		exit(1);
	}

	long int l;
	int base;
	char *endptr;

	base = atoi(argv[2]);
	fprintf(stdout, "converts %s to long int base %d\n", argv[1], base);

	errno = 0;

	double d;
	//double strtod(const char *nptr, char **endptr);
	//float strtof(const char *nptr, char **endptr);
	//long double strtold(const char *nptr, char **endptr);
	d = strtod(argv[1], &endptr);
	if(errno != 0){
		fprintf(stderr, "strtol error: %s\n", strerror(errno));
		exit(1);
	}
	fprintf(stdout, "result is %f, valid str is %s\n", d, endptr);

	errno = 0;

	//long int strtol(const char *nptr, char **endptr, int base);
	l = strtol(argv[1], &endptr, base);
	if(errno != 0){
		fprintf(stderr, "strtol error: %s\n", strerror(errno));
		exit(1);
	}
	fprintf(stdout, "result is %ld, valid str is %s\n", l, endptr);
	
	
	
	return 0;
}
