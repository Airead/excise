/* come from APUE */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int glob = 6;
char buf[] = "a write to stdout\n";

int main(int argc, char *argv[])
{
	int var;
	pid_t pid;

	var = 88;
	
	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1){
		perror("write error");
		exit(1);
	}
	
	fprintf(stdout, "Before fork\n"); /* we don't flush stdout */
	
	// pid_t fork(void);
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid == 0){
		/* child process */
		glob++;
		var++;
	}else{
		/* parent */
		sleep(2);
	}

	fprintf(stdout, "pid = %d, glob = %d, var = %d\n", 
		getpid(), glob, var);
	
	exit(0);
}
