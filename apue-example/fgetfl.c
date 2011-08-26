/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 8月 23 21:44:59 CST			*
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

void dump_flags(int flags);

int main(int argc, char *argv[])
{
	int flags;

	flags = fcntl(0, F_GETFL);
	printf("stdin: ");
	fprintf(stdout, "0: %#08x\n", flags);
	dump_flags(flags);

	flags = fcntl(0, F_GETFL);
	printf("stdout: ");
	fprintf(stdout, "0: %#08x\n", flags);
	dump_flags(flags);

	flags = fcntl(0, F_GETFL);
	printf("stderr: ");
	fprintf(stdout, "0: %#08x\n", flags);
	dump_flags(flags);
	
	return 0;
}

void dump_flags(int flags)
{
	int access_mode;
	
	access_mode = flags & O_ACCMODE;
	switch(access_mode){
	case O_RDONLY:
		fprintf(stdout, "read only\n");
		break;
	case O_WRONLY:
		fprintf(stdout, "write only\n");
		break;
	case O_RDWR:
		fprintf(stdout, "read/write only\n");
		break;
	}


	if(flags & O_APPEND){
		fprintf(stdout, "O_APPEND\n");
	}
	if(flags & O_CREAT){
		fprintf(stdout, "O_CREAT\n");
	}
	if(flags & O_TRUNC){
		fprintf(stdout, "O_TRUNC\n");
	}
	if(flags & O_EXCL){
		fprintf(stdout, "O_EXCL\n");
	}
	
}
