/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 16:15:22 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int setuid(uid_t uid);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void printallids()
{
	//pid_t getpid(void);
	fprintf(stdout, "pid = %lu\t\t", (unsigned long)getpid());
	
	//pid_t getppid(void);
	fprintf(stdout, "ppid = %lu\t\t", (unsigned long)getppid());
	
	//uid_t getuid(void);
	fprintf(stdout, "uid = %lu\n", (unsigned long)getuid());

	//uid_t geteuid(void);
	fprintf(stdout, "euid = %lu\t\t", (unsigned long)geteuid());
       
	//gid_t getgid(void);
	fprintf(stdout, "gid = %lu\t\t", (unsigned long)getgid());

	//gid_t getegid(void);
	fprintf(stdout, "egid = %lu\n", (unsigned long)getegid());
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "usage: %s <uid_t>\n", argv[0]);
		exit(1);
	}
	
	fprintf(stdout, "Before setuid\n");
	printallids();
	
	uid_t uid;
	
	//unsigned long int strtoul(const char *nptr, char **endptr, int base);
	uid = (uid_t)strtoul(argv[1], NULL, 10); 
	
	//int setuid(uid_t uid);
	if(setuid(uid) < 0){
		perror("setuid");
		exit(1);
	}else{
		fprintf(stdout, "set uid success\n");
	}

	fprintf(stdout, "\nAfter set uid\n");
	printallids();
	
	return 0;
}
