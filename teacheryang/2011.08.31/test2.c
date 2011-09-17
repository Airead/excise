#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void signal_handler(int sig);

int main(int argc, char **argv)
{
#if 0
  int getrlimit(int resource, struct rlimit *rlim);
#endif

  // RLIMIT_CORE
  //    Maximum size of core file. When 0 no  core  dump  files
  //    are created.  When non-zero, larger dumps are truncated
  //    to this size.

  struct rlimit rlim;

#if 0
  struct rlimit
  {
    rlim_t rlim_cur;		/* Soft limit */
    rlim_t rlim_max;		/* Hard limit (ceiling for rlim_cur) */
  };
#endif

  rlim.rlim_cur = 1024 * 1024 * 4;
  rlim.rlim_max = 1024 * 1024 * 16;

  //int setrlimit(int resource, const struct rlimit *rlim);
  if (setrlimit(RLIMIT_CORE, &rlim) < 0)
  {
    fprintf(stderr, "Change core files size failed: %s\n", strerror(errno));
    exit(1);
  }

  //typedef void (*sighandler_t) (int);
  //sighandler_t signal(int signum, sighandler_t handler);

  //signal(SIGQUIT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  // FAILED: signal(SIGKILL, signal_handler);

  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);

    sleep(1);
  }

  return 0;
}

void signal_handler(int sig)
{
  fprintf(stderr, "Caught signal %d.\n", sig);
}
