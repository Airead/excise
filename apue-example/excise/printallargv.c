/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 12:34:56 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * print all arguments
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	char **p;
	
	/* method: one */
	fprintf(stdout, "----------------------------------------\n");
	fprintf(stdout, "method one:\n");
	p = argv; i = 0;
	while(*p != NULL){
		fprintf(stdout, "[%d]%s\n", i++, *p++);
	}

	/* method: two */
	fprintf(stdout, "----------------------------------------\n");
	fprintf(stdout, "method two:\n");
	for(i = 0; i < argc; i++){
		fprintf(stdout, "[%d]%s\n", i, argv[i]);
	}

	/* method: three */
	char *arg[100];

	fprintf(stdout, "----------------------------------------\n");
	fprintf(stdout, "method three:\n");

	p = arg;
	while(*argv != NULL){
		*p++ = *argv++;
	}
	*p = NULL;

	p = arg; i = 0;
	while(*p != NULL){
		fprintf(stdout, "[%d]%s\n", i++, *p++);
	}

	fprintf(stdout, "----------------------------------------\n");

	return 0;
}
