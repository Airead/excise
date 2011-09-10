/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 10 20:16:34 CST			*
 ********************************************************
 *		after studying C 54 days		*
 *		after studying APUE 19 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * redirect stdin
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
	int i;
	int ch;
	int fd;
	int stdin_fd;

	//int dup(int oldfd);
	stdin_fd = dup(STDIN_FILENO);
	
	//int open(const char *pathname, int flags);
	fd = open("1.tmp", O_RDONLY);
	

	//int dup2(int oldfd, int newfd);
	dup2(fd, STDIN_FILENO);
	
	execlp("grep", "grep", "sh", NULL);

	return 0;
}
