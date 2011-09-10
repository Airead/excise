/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 10 16:52:01 CST			*
 ********************************************************
 *		after studying C 54 days		*
 *		after studying APUE 19 days		*
 ********************************************************/

/*
 * This program demonstrates redirect output of exec
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
	int fd;
	int pipefd[2];
	pid_t pid;
	int stdout_fd, stdin_fd;
	char *args_ls[] = {"ls", "--color=auto", NULL};
	
	//int open(const char *pathname, int flags, mode_t mode);
	if((fd = open("1.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0){
		perror("create file failed");
	}

	//int pipe(int pipefd[2]);
	if(pipe(pipefd) < 0){
		perror("pipe failed");
		exit(1);
	}


	//int dup(int oldfd);
	if((stdout_fd = dup(STDOUT_FILENO)) < 0){
		perror("dup() failed");
		exit(1);
	}

	//int dup(int oldfd);
	if((stdin_fd = dup(STDIN_FILENO)) < 0){
		perror("dup() failed");
		exit(1);
	}


	//int dup2(int oldfd, int newfd);
	if(dup2(fd, STDOUT_FILENO) < 0){
		perror("dup2() failed");
		exit(1);
	}

	/* fork for ls */
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid == 0){
		/* child process */
		
		//int execvp(const char *path, char *const argv[]);
		if(execvp("ls", args_ls) < 0){
			perror("execvp failed");
			exit(1);
		}
		
	} /* child process end */
	
	
	//pid_t waitpid(pid_t pid, int *status, int options);
	waitpid(pid, NULL, 0);

#if 0
	//int dup2(int oldfd, int newfd);
	if(dup2(stdout_fd, STDOUT_FILENO) < 0){
		perror("dup2() failed");
		exit(1);
	}
	close(stdout_fd);

	fprintf(stdout, "hello world!\n");

#endif
	close(fd);
	
	return 0;
}
