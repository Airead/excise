/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 22:29:38 CST			*
 ********************************************************
 *		after studying C 36 days		*
 *		after studying APUE 1 days		*
 ********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/* This program is redirect stdout */
int main(int argc, char *argv[])
{
	int fd;
	int tmpfd;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	//step 1. open a file(fd)
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0){
		if(errno == EEXIST){
			fd = open(argv[1], O_RDWR | O_TRUNC);
		}else{
			perror("open error");
			exit(1);
		}
	}else{
		fprintf(stdout, "open %s success\n", argv[1]);
	}
	
	//step 2. redirect stdout to fd
	//int dup(int oldfd);
	if((tmpfd = dup(STDOUT_FILENO)) < 0){
		perror("dup error: ");
		close(fd);
		exit(1);
	}

	//int dup2(int oldfd, int newfd);
	if((dup2(fd, STDOUT_FILENO)) < 0){
		perror("dup error: ");
		close(fd);
		exit(1);
	}

	//step 3. print "hello world" to stdout
	fprintf(stdout, "hello world\n");
	fflush(stdout);
	//step 3.5 recover stdout
	//int dup2(int oldfd, int newfd);
	if(dup2(tmpfd, STDOUT_FILENO) < 0){
		perror("recovery stdout: ");
		close(fd);
		close(tmpfd);
		exit(1);
	}

	//step 3.6 print "world hello" to stdout
	fprintf(stdout, "world hello\n");

	//step 4. close fd
	close(fd);
	close(tmpfd);
	//sleep(1000);
}
