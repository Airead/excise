/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 26 12:28:01 CST			*
 ********************************************************
 *		after studying C 39 days		*
 *		after studying APUE 4 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * mode_t umask(mode_t mask);
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{

	int fd;

	//mode_t umask(mode_t mask);
	umask(0);
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open("1.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0){
		fprintf(stderr, "create 1.tmp failed: %s\n", strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "create 1.tmp success\n");
	}
	close(fd);

	//mode_t umask(mode_t mask);
	umask(070);
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open("2.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0){
		fprintf(stderr, "create 2.tmp failed: %s\n", strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "create 2.tmp success\n");
	}
	close(fd);

	//mode_t umask(mode_t mask);
	umask(007);
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open("3.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0){
		fprintf(stderr, "create 3.tmp failed: %s\n", strerror(errno));
		exit(1);
	}else{
		fprintf(stdout, "create 3.tmp success\n");
	}
	close(fd);

	return 0;
}
