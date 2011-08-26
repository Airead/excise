/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 21:50:09 CST			*
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

/* - if oldfd lseek, affact newfd or not
 * - if newfd write operation, affact oldfd or not
 * - if newfd read operation, affact oldfd or not 
 */

int main(int argc, char *argv[])
{
	int fd;
	innt nfd;
	char buf[5];

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	//step 1. open a file(fd)
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0){
		//EEXIST pathname already exists
		if(errno == EEXIST){
			if((fd = open(argv[1], O_RDWR)) < 0){
				fprintf(stderr, "open %s error\n", argv[1]);
				exit(1);
			}
		}
	}else{
		fprintf(stdout, "open %s success\n", argv[1]);
	}

	//step 2. dup file descriptor(nfd)
	//int dup(int oldfd);
	if((nfd = dup(fd)) < 0){
		perror("dup error");
	}
	
	//step 3. write "1234" to fd
	//ssize_t write(int fd, const void *buf, size_t count);
	write(fd, "1234", 4);
	fprintf(stdout, "write to fd 1234\n");

	//step 4. write "5678" to nfd
	//ssize_t write(int fd, const void *buf, size_t count);
	write(nfd, "5678", 4);
	fprintf(stdout, "write to fd 5678\n");

	//step 5. move to file begin
	//off_t lseek(int fd, off_t offset, int whence);
	lseek(fd, 0, SEEK_SET);

	//step 6. nfd show 1-4 chars
	memset(buf, 0, sizeof(buf));
	//ssize_t read(int fd, void *buf, size_t count);
	if(read(nfd, buf, 4) < 0){
		perror("read nfd error");
		exit(1);
	}else{
		fprintf(stdout, "nfd's content: ");
		fprintf(stdout, "%s\n", buf);
	}

	//step 7. fd show 5-8 chars
	memset(buf, 0, sizeof(buf));
	//ssize_t read(int fd, void *buf, size_t count);
	if(read(fd, buf, 4) < 0){
		perror("read fd error");
		exit(1);
	}else{
		fprintf(stdout, "fd's content: ");
		fprintf(stdout, "%s\n", buf);
	}

	//step 8. close fd,nfd
	close(fd);
	close(nfd);

	return 0;
}
