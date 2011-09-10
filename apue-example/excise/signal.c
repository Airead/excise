/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 20:20:55 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates functioin
 * typedef void (*sighandler_t)(int);
 * sighandler_t signal(int signum, sighandler_t handler);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

static void sig_usr(int);	/* one handler for both signals */

int main(int argc, char *argv[])
{
	//typedef void (*sighandler_t)(int);
	//sighandler_t signal(int signum, sighandler_t handler);
	if(signal(SIGUSR1, sig_usr) == SIG_ERR){
		perror("can't catch SIGUSR1");
	}
	if(signal(SIGUSR2, sig_usr) == SIG_ERR){
		perror("can't catch SIGUSR2");
	}
	while(1){
		pause();
	}
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1){
		fprintf(stdout, "received SIGUSR1\n");
	}else if(signo == SIGUSR2){
		fprintf(stdout, "received SIGUSR2\n");
	}else{
		fprintf(stdout, "received signal %d\n", signo);
	}
}
