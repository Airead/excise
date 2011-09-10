/* Come from APUE */

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

	if((pid = fork()) < 0){
		perror("fork first error");
		exit(1);
	}else if(pid == 0){
		/* first child */
		if((pid = fork()) < 0){
			perror("fork second error");
			exit(1);
		}else if(pid > 0){
//			wait(NULL); /* test it! */
			exit(0); /* parent from second fork == first child */
		}
		/* We're the second child; our parent becomes init as soon
		 * as our real parent calls exit() int the statement above.
		 * Here's where we'd continue executing, knowing that when
		 * we're done, init will reap our status
		 */
		sleep(2);

		fprintf(stdout, "second child, parent pid = %d\n", getppid());

		exit(0);
	}

	if(waitpid(pid, NULL, 0) != pid){
		/* wait for first child */
		perror("waitpid error");
	}

	/*
	 * We're the parent (the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 */
	exit(0);
}
