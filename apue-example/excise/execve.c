/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 14:30:16 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int execve(const char *filename, char *const argv[],
 *           char *const envp[]);
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
		fprintf(stderr, "usage: %s <elfname> [args...]\n", argv[0]);
		exit(1);
	}else if(argc > 100){
		fprintf(stderr, "args numbers shoud less than 100\n");
		exit(1);
	}
	
	char *newenviron[] = {"USER=AIREAD", "EMAIL=FGH1987168@GMAIL.COM", NULL};
	//int execve(const char *filename, char *const argv[],
	//           char *const envp[]);
	if(execve(argv[1], argv + 1, newenviron) < 0){
		fprintf(stderr, "execve %s failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	return 0;
}
