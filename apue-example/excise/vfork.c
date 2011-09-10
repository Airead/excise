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

int main(int argc, char *argv[])
{
	int var;
	pid_t pid;

	var = 88;
	
	fprintf(stdout, "before vfork\n");

	// pid_t vfork(void);
	if((pid = vfork()) < 0){
		perror("vfork");
		exit(1);
	}else if(pid == 0){
		/* child process */
		glob++;
		var++;
		_exit(0);	/* child terminates: not exit(0) */
	}

	fprintf(stdout, "pid = %d, glob = %d, var = %d\n", 
		getpid(), glob, var);
	
	exit(0);
}
