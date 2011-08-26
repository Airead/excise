/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 24 15:52:06 CST			*
 ********************************************************
 *		after studying C 37 days		*
 *		after studying APUE 2 days		*
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
	int flags;

	if((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open error: ");
		exit(1);
	}else{
		printf("open success\n");
	}

	if((flags = fcntl(fd, F_GETFL)) < 0){
		perror("F_GETFL error: ");
		exit(1);
	}else{
		fprintf(stdout, "flags = %d\n", flags);
	}
	
	close(fd);

	return 0;
}
