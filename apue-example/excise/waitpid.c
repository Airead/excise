/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 05 23:17:12 CST			*
 ********************************************************
 *		after studying C 49 days		*
 *		after studying APUE 14 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * pid_t waitpid(pid_t pid, int *status, int options);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid[2];
	pid_t termpid = 0;
	
	//step 1. fork two child
	//pid_t fork(void);
	if((pid[0] = fork()) < 0){
		fprintf(stderr, "fork 1 failed: %s\n", strerror(errno));
		exit(1);
	}else if(pid[0] == 0){
		/* child 1 process */
		fprintf(stdout, "child 1 pid: %lu, sleep 5\n", (unsigned long)getpid());

		//step 2. child 1 process sleep 5 seconds
		sleep(5);
		exit(0);
	}

	if((pid[1] = fork()) < 0){
		fprintf(stderr, "fork 2 failed: %s\n", strerror(errno));
		exit(1);
	}else if(pid[1] == 0){
		/* child 1 process */
		fprintf(stdout, "child 2 pid: %lu, sleep 2\n", (unsigned long)getpid());
		//step 2.5. child 2 process sleep 3 seconds
		sleep(2);
		exit(0);
	}
	
	int status;
	//step 3. parent process wait child
	//pid_t waitpid(pid_t pid, int *status, int options);
//	termpid = waitpid(pid[0], &status, WNOHANG); /* test it! */
	termpid = waitpid(pid[0], &status, 0);
	
	//step 4. print waited pid
	fprintf(stdout, "termination process pid: %lu\n", 
		(unsigned long)termpid);
	
	return 0;
}
