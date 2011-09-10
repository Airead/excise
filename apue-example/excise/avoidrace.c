/* Come from APUE */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static void charatattime(char *str);

int main(int argc, char *argv[])
{
	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("fork failed");
		exit(1);
	}else if(pid == 0){
		sleep(10);
		charatattime("output from child\n");
	}else{
		charatattime("output from parent\n");
	}

	exit(0);
}

static void charatattime(char *str)
{
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != '\0';){
		putc(c, stdout);
	}
}
