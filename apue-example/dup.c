/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 22:28:24 CST			*
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


int main(int argc, char *argv[])
{
	int fd;

	if(argc < 2){
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}
/* creat() is equivalent to open() with flags equal to O_CREAT|O_WRONLY|O_TRUNC. */

	if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644)) < 0){
		if(errno == EEXIST){
			if((fd = open(argv[1], O_WRONLY | O_TRUNC)) < 0){
				fprintf(stderr, "open %s error\n", argv[1]);
			}else{
				perror("open error:");
				exit(1);
			}
		}else{
			fprintf(stderr, "Open file %s for reading failed: %s"
				"\n", argv[1], strerror(errno));
		exit(1);
		}
	}

	fprintf(stdout, "Open file %s for reading successfully.\n", argv[1]);

	int newfd;
	if((newfd = fcntl(fd, F_DUPFD, 100)) < 0){
		fprintf(stderr,"fcntl(F_DUPFD) error: %s\n", strerror(errno));
	}else{
		fprintf(stdout, "dup success %d\n", newfd);
	}

	int newfd2;
	/* int dup(int oldfd); */
	if((newfd2 = dup(newfd)) < 0){
		fprintf(stderr, "dup error: %s\n", strerror(errno));
	}else{
		fprintf(stdout, "dup success %d\n", newfd2);
	}
	
	int newfd3 = 6;
	/* int dup2(int oldfd, int newfd); */
	if((newfd3 = dup2(newfd2, newfd3)) < 0){
		fprintf(stderr, "dup error %s\n", strerror(errno));
	}else{
		fprintf(stdout, "dup success %d\n", newfd3);
	}

	close(fd);
	close(newfd);
	close(newfd2);
	close(newfd3);

	return 0;
}
