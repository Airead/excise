/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 10 16:52:01 CST			*
 ********************************************************
 *		after studying C 54 days		*
 *		after studying APUE 19 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * redirect output of "ls" to input of grep
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_MAX 100

int main(int argc, char *argv[])
{
	char rbuf[1000];
	ssize_t n;
	int i;
	int pipefd[2];
	pid_t pid[2];
	char *args_ls[] = {"ls", "--color=auto", NULL};
	char *args_grep[] = {"grep", "sh", NULL};
	
	//int pipe(int pipefd[2]);
	if(pipe(pipefd) < 0){
		perror("pipe failed");
		exit(1);
	}

	/* fork for ls */
	if((pid[0] = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid[0] == 0){
		/* child process */
		close(pipefd[0]);

		sleep(5);

		//int dup2(int oldfd, int newfd);
		if(dup2(pipefd[1], STDOUT_FILENO) < 0){
			perror("ls dup2 stdout failed\n");
		}

		//int execvp(const char *path, char *const argv[]);
		if(execvp("ls", args_ls) < 0){
			perror("execvp failed");
			exit(1);
		}
		
	} /* child process end */


	/* fork for grep */
	if((pid[1] = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid[1] == 0){
		/* child process */
		close(pipefd[1]);

		//int dup2(int oldfd, int newfd);
		dup2(pipefd[0], STDIN_FILENO);


		//int execvp(const char *path, char *const argv[]);
		if(execvp("grep", args_grep) < 0){
			perror("execvp failed");
			exit(1);
		}
	
	} /* child process end */



	/* parent process */
	close(pipefd[1]);
	close(pipefd[0]);

	for(i = 0; i < 2; i++){
		//pid_t waitpid(pid_t pid, int *status, int options);
		waitpid(pid[i], NULL, 0);
	}

#if 0
	//ssize_t read(int fd, void *buf, size_t count);
	while((n = read(pipefd[0], rbuf, sizeof(rbuf))) != 0){
		if(n < 0){
			perror("[%lu]parent: read failed");
			exit(1);
		}
		fprintf(stdout, "[%lu]parent: receive '%s'\n", (unsigned long)getpid(), rbuf);
	}

#endif
//	close(stdout_fd);
//	close(stdin_fd);

	return 0;
}
