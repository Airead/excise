 /********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 14:58:44 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int unlink(const char *pathname);
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	//int unlink(const char *pathname);
	if(unlink(argv[1]) < 0){
		fprintf(stderr, "unlink %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "unlink %s success\n", argv[1]);
	}

	return 0;
}
