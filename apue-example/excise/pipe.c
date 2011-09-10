/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 10 19:17:49 CST			*
 ********************************************************
 *		after studying C 54 days		*
 *		after studying APUE 19 days		*
 ********************************************************/

/*
 * This program demonstrates function
 * int pipe(int pipefd[2]);
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
	int pipefd[2];
	char wbuf[100], rbuf[100];
	pid_t pid;
	ssize_t n;

	//int pipe(int pipefd[2]);
	if(pipe(pipefd) < 0){
		perror("pipefd");
		exit(1);
	}

	//pid_t fork(void);
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid == 0){
		/* child process */
		close(pipefd[0]);
		
//		sleep(1);
		

		memset(wbuf, 0, sizeof(wbuf));		
		//int snprintf(char *str, size_t size, const char *format, ...);
		snprintf(wbuf, sizeof(wbuf), "[%lu]child: Ready to write\n", (unsigned long)getpid());
		//ssize_t write(int fd, const void *buf, size_t count);
		write(STDOUT_FILENO, wbuf, sizeof(wbuf));


		//int dup2(int oldfd, int newfd);
		if(dup2(pipefd[1], STDOUT_FILENO) < 0){
			perror("dup2");
			exit(1);
		}

		memset(wbuf, 0, sizeof(wbuf));		
		snprintf(wbuf, sizeof(wbuf), "[%lu]child: i want to write at stdout.\n",(unsigned long)getpid());
		//ssize_t write(int fd, const void *buf, size_t count);
		write(STDOUT_FILENO, wbuf, sizeof(wbuf));

		memset(wbuf, 0, sizeof(wbuf));
		//char *strncpy(char *dest, const char *src, size_t n);
		strncpy(wbuf, "hello parent", sizeof(wbuf) - 1);
		
		//ssize_t write(int fd, const void *buf, size_t count);
		write(STDOUT_FILENO, wbuf, sizeof(wbuf));

		
		
		exit(1);
	} /* child process end */

	/* parent process */
	close(pipefd[1]);

	fprintf(stdout, "[%lu]parent: parent run\n", (unsigned long)getpid());

	sleep(5);

	//ssize_t read(int fd, void *buf, size_t count);
	while((n = read(pipefd[0], rbuf, sizeof(rbuf))) != 0){
		if(n < 0){
			perror("[%lu]parent: read failed");
			exit(1);
		}
		fprintf(stdout, "[%lu]parent: receive '%s'\n", (unsigned long)getpid(), rbuf);
	}



	return 0;
}
