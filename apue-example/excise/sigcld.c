/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 21:43:20 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * avoid zombie
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
#include <signal.h>

void sig_cld(int signo)
{
	int status;
	pid_t pid;

	if(signal(SIGCLD, sig_cld) == SIG_ERR){
		perror("signal(SIGCLD) failed");
		exit(1);
	}
	
	// pid_t wait(int *status);
	if((pid = wait(&status)) < 0){
		perror("wait failed");
		exit(1);
	}
	
	fprintf(stdout, "process %d exit\n", pid);
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int i;

	//typedef void (*sighandler_t)(int);
	//sighandler_t signal(int signum, sighandler_t handler);
	signal(SIGCLD, sig_cld);

	for(i = 0; i < 10; i++){
		//pid_t fork(void);
		if((pid = fork()) < 0){
			perror("fork");
			exit(1);
		}else if(pid == 0){
			/* child process */
			fprintf(stdout, "[%d]I am child\n", getpid());
			sleep(i + 2);
			exit(0);
		}
	}
	/* parent process */
	fprintf(stdout, "[%d]I am parent\n", getpid());
	
	for(i = 0; i < 10; i++){
		pause();
	}
	
	return 0;
}
