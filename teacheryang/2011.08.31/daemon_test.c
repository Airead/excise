#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void daemon_init(const char *ident);
void signal_handler(int sig);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  daemon_init(argv[0]);

  syslog(LOG_USER | LOG_DEBUG, "[%d]Starting ...", getpid());

  //typedef void (*sighandler_t) (int);
  //sighandler_t signal(int signum, sighandler_t handler);
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGQUIT, signal_handler);

  for (;;)
  {
    if (global_exit_flag > 0)
    {
      syslog(LOG_USER | LOG_DEBUG, "It's time to exit, see you later.");
      break;
    }

    // do something here.
    sleep(1);
  }

  closelog();

  return 0;
}

//--------------------------------------------------------------------
// Signal handler
//--------------------------------------------------------------------
void signal_handler(int sig)
{
  //fprintf(stdout, "Caught signal %d.\n", sig);
  syslog(LOG_USER | LOG_DEBUG, "Caught signal %d.\n", sig);
  global_exit_flag++;
}

//--------------------------------------------------------------------
// Daemon initialize
//--------------------------------------------------------------------
void daemon_init(const char *ident)
{
  pid_t pid;

  // step 1, fork, parent termination
  //pid_t fork(void);
  if ((pid = fork()) < 0)
  {
    // failed
    fprintf(stderr, "fork() failed: %s\n", strerror(errno));
  }
  else if (pid > 0)
  {
    // parent process
    exit(0);
  }

  // step 2, setsid(), create new session,
  // pid_t setsid(void);
  setsid();

  // step 3, chdir()
  // int chdir(const char *path);
  chdir("/");

  // step 4, set new umask value
  // mode_t umask(mode_t mask);
  umask(0);

  // step 5, close open files
  long open_max;
  int i;

  // long sysconf(int name);
  open_max = sysconf(_SC_OPEN_MAX);

  for (i = 0; i < open_max; i++)
  {
    close(i);
  }

  // step 6, open syslog

#if 0
  void openlog(const char *ident, int option, int facility);
  void syslog(int priority, const char *format, ...);
  void closelog(void);
#endif

  openlog(ident, LOG_PID, LOG_USER | LOG_DEBUG);
}
