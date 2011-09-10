/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 20:36:59 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates a case
 * Call a nonreentrant function from a signal handler
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <signal.h>

static void my_alarm(int signo)
{
	struct passwd *rootptr;
	
	fprintf(stdout, "in singal handler\n");
	if((rootptr = getpwnam("root")) == NULL){
		perror("getpwnam(root) failed");
	}
//	fprintf(stdout, "%s\n", rootptr->pw_name);
	alarm(1);
	usleep(500000);
}

int main(int argc, char *argv[])
{
	struct passwd *ptr;
	int i = 0;

	signal(SIGALRM, my_alarm);
	alarm(1);

	while(1){
		if((ptr = getpwnam("airead")) == NULL)
			perror("getpwnam error");
		
		fprintf(stdout, "%d\t", strcmp(ptr->pw_name, "airead"));
		
		if(strcmp(ptr->pw_name, "airead") != 0){
			fprintf(stdout, "return value corrupted!, pw_name = %s\n",
				ptr->pw_name);
			exit(1);
		}
		fprintf(stdout, "[%d]%s\n", i++, ptr->pw_name);
		usleep(100000);
	}
}
