/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 23:30:49 CST			*
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
#include <sys/mman.h>

#define MAPPED_LENGTH 1024

int main(int argc, char *argv[])
{
	int fd;
	
	if((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0){
		fprintf(stderr, "open file %s for r/w failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	fprintf(stdout, "open %s success\n", argv[1]);

	void *addr;
	addr = mmap(NULL, MAPPED_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED){
		fprintf(stderr, "mapping failed\n");
		exit(1);
	}
	printf("mapping success %#08x\n", (int)addr);

	char msg[] = "hello word\n";
	lseek(fd, MAPPED_LENGTH - 1, SEEK_SET);
	write(fd, "x", 1);
	
	memcpy(addr + 200, msg, strlen(msg));

	if((munmap(addr, MAPPED_LENGTH)) < 0){
		fprintf(stderr, "unmap failed: %s\n", strerror(errno));
	}

	close(fd);

	return 0;
}
