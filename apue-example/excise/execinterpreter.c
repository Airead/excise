/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 17:07:29 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * exec an interpreter file
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
	pid_t pid;
	
	//pid_t fork(void);
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid == 0){
		/* child process */
		//int execl(const char *path, const char *arg, ...);
		if(execl("/home/airead/study/APUE/example/excise/testinterp",
			 "testinterp", "myarg1", "MY ARG2", NULL) < 0){
			perror("execl failed");
			exit(1);
		}
	}

	/* parent process */
	if(waitpid(pid, NULL, 0) < 0){
		perror("waitpid error");
	}

	exit(0);
}
