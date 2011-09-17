#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv)
{
  char *p;

  struct rlimit rlim;

#if 0
  struct rlimit
  {
    rlim_t rlim_cur;		/* Soft limit */
    rlim_t rlim_max;		/* Hard limit (ceiling for rlim_cur) */
  };
#endif

  //int getrlimit(int resource, struct rlimit *rlim);
  getrlimit(RLIMIT_CORE, &rlim);

  fprintf(stdout, "soft: 0x%08lx, hard: 0x%08lx\n", rlim.rlim_cur, rlim.rlim_max);

  //int setrlimit(int resource, const struct rlimit *rlim);
#if 0
  rlim.rlim_cur = 100;
  rlim.rlim_max = 0;
#endif

  *p = 0;

  return 0;
}
