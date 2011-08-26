#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * Open a file and check its
 *   1. File descriptor flags
 *      - FD_CLOEXEC
 *   2. File status flags
 *      - O_RDONLY 00000000
 *      - O_WRONLY 00000001
 *      - O_RDWR 00000002
 *      - O_CREAT 00000100
 *      - O_EXCL 00000200
 *      - O_NOCTTY
 *      - O_TRUNC
 *      - O_APPEND 00002000
 */
int main(int argc, char *argv[])
{
	int fd;
	int flags;
	int newflags;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	//1. Open a file
	//int open(const char *pathname, int flags)
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL | O_APPEND)) < 0){
		/* error */
		//EEXIST pathname already exists 
		if(errno == EEXIST){
			if((fd = open(argv[1], O_RDWR | O_APPEND)) < 0){
				/* error */
				fprintf(stderr, "open error: %s\n", strerror(errno));
				exit(0);
			}
		}
	}else{
		fprintf(stdout, "Open %s success\n", argv[0]);
	}
	
	//2. get and showfile descriptor flags
	//int fcntl(int fd, int cmd, ... /* arg */ );
	//F_GETFD  Value of flags
	flags = fcntl(fd, F_GETFD);
	fprintf(stdout, "F_GETFD: %d\n", flags);
	
	//3. get file status flags
	//F_GETFL  Value of flags.
	flags = fcntl(fd, F_GETFL);
	fprintf(stdout, "before chage flags\n");
	fprintf(stdout, "F_GETFL: %d\n", flags);

	//4. change flags
	newflags = flags & ~O_APPEND;
	//int fcntl(int fd, int cmd, ... /* arg */ );
	fcntl(fd, F_SETFL, newflags);

	//5. show flags
	fprintf(stdout, "after change flags\n");
	fprintf(stdout, "F_GETFL: %d\n", newflags);

	//6. close file
	close(fd);
}
