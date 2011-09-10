/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 06 19:02:36 CST			*
 ********************************************************
 *		after studying C 50 days		*
 *		after studying APUE 15 days		*
 ********************************************************/

/*
 * This program demonstrates method
 * get time and execute all command-line arguments
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/wait.h>

static void do_cmd(char *cmd);
static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);
void pr_exit(int status);

int main(int argc, char *argv[])
{
	int i;
	
	//void setbuf(FILE *stream, char *buf);
	setbuf(stdout, NULL);
	for(i = 1; i < argc; i++){
		do_cmd(argv[i]);
	}
	exit(0);
}

/*
 * execute and time the "cmd"
 */
static void do_cmd(char *cmd)
{
#if 0
	struct tms {
		clock_t tms_utime;  /* user time */
		clock_t tms_stime;  /* system time */
		clock_t tms_cutime; /* user time of children */
		clock_t tms_cstime; /* system time of children */
	};
#endif
	struct tms tmsstart, tmsend;
	clock_t start, end;
	int status;

	fprintf(stdout, "\ncommand: %s\n", cmd);

	//clock_t times(struct tms *buf);
	if((start = times(&tmsstart)) == -1){ /* starting values */
		perror("times error");
		exit(1);
	}
	
	//int system(const char *command);
	if((status = system(cmd)) < 0){
		perror("system() error");
		exit(1);
	}

	if((end = times(&tmsend)) == -1){
		perror("times error");
		exit(1);
	}

	pr_times(end-start, &tmsstart, &tmsend);
	pr_exit(status);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
	static long clktck = 0;

	if(clktck == 0){	/* fetch clock ticks per second first time */
		if((clktck = sysconf(_SC_CLK_TCK)) < 0){
			perror("sysconf error");
			exit(1);
		}
	}
	
	fprintf(stdout, " real: %7.2f\n", real / (double)clktck);
	fprintf(stdout, " user: %7.2f\n",
		(tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
	fprintf(stdout, " sys: %7.2f\n",
		(tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
	fprintf(stdout, " child user: %7.2f\n",
		(tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
	fprintf(stdout, " child sys: %7.2f\n",
		(tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clktck);
}

void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n",
		       WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",
		       WTERMSIG(status),
#ifdef	WCOREDUMP
		       WCOREDUMP(status) ? " (core file generated)" : "");
#else
	"");
#endif
        else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",
		       WSTOPSIG(status));
}
