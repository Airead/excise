/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 20:41:22 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * get all process id
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
	//pid_t getpid(void);
	fprintf(stdout, "pid = %lu\n", (unsigned long)getpid());
	
	//pid_t getppid(void);
	fprintf(stdout, "ppid = %lu\n", (unsigned long)getppid());
	
	//uid_t getuid(void);
	fprintf(stdout, "uid = %lu\n", (unsigned long)getuid());

	//uid_t geteuid(void);
	fprintf(stdout, "euid = %lu\n", (unsigned long)geteuid());
       
	//gid_t getgid(void);
	fprintf(stdout, "gid = %lu\n", (unsigned long)getgid());

	//gid_t getegid(void);
	fprintf(stdout, "egid = %lu\n", (unsigned long)getegid());
       
	return 0;
}
