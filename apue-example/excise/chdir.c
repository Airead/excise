/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 27 10:30:57 CST			*
 ********************************************************
 *		after studying C 40 days		*
 *		after studying APUE 5 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int chdir(const char *path);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

int main(int argc, char *argv[])
{
	char buf[NAME_MAX + 1];
	
	memset(buf, 0, NAME_MAX + 1);
	//char *getcwd(char *buf, size_t size);
	if(getcwd(buf, NAME_MAX) == NULL){
		perror("getcwd");
		exit(1);
	}else{
		fprintf(stdout, "current working directory: `%s'\n", buf);
	}
	
	//int chdir(const char *path);
	if(chdir("/tmp") < 0){
		perror("chdir");
		exit(1);
	}

	memset(buf, 0, NAME_MAX + 1);
	//char *getcwd(char *buf, size_t size);
	if(getcwd(buf, NAME_MAX) == NULL){
		perror("getcwd");
		exit(1);
	}else{
		fprintf(stdout, "current working directory: `%s'\n", buf);
	}

	return 0;
}
