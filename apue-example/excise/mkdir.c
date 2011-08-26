 /********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 18:49:08 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int mkdir(const char *pathname, mode_t mode);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <dirpath>\n", argv[0]);
		exit(1);
	}

	//int mkdir(const char *pathname, mode_t mode);
	if(mkdir(argv[1], 0755) < 0){
		fprintf(stderr, "create %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}else{
		fprintf(stderr, "create %s success\n", argv[1]);
	}

	return 0;
}
