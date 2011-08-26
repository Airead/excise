/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 22:44:33 CST			*
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

/* This program can hide inputed password */

int main(int argc, char *argv[])
{
	int fd;
	char buf[100];
	char filename[] = "/tmp/my_tmp_pwdbuf";
	//step 1. open a temporary file(fd)
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600)) < 0){
		if(errno == EEXIST){
			//int open(const char *pathname, int flags);
			fd = open(filename, O_RDWR | O_TRUNC);
		}else{
			perror("open error: ");
			exit(1);
		}
	}else{
		fprintf(stdout, "open tmpbuf success\n");
	}

	//step 2. redirect stdin to fd
	//int dup2(int oldfd, int newfd);
	if(dup2(fd, STDIN_FILENO) < 0){
		perror("dup error: ");
		close(fd);
		exit(1);
	}
	//step 2.3 input password
	//char *fgets(char *s, int size, FILE *stream);
	fgets(buf, sizeof(buf), stdin);
	//step 3. show inputed passwd
	//off_t lseek(int fd, off_t offset, int whence);
	lseek(fd, 0, SEEK_SET);
	//void *memset(void *s, int c, size_t n);
	memset(buf, 0, sizeof(buf));
	//ssize_t read(int fd, void *buf, size_t count);
	read(fd, buf, sizeof(buf));
	fprintf(stdout, "%s", buf);

	//step 4. close fd
	close(fd);

	//step 5. remove fd(unlink filename)
	//int unlink(const char *pathname);
	unlink(filename);

	return 0;
}
