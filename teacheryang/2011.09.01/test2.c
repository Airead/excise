#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

void signal_handler(int signum, siginfo_t * info, void *data);

int main(int argc, char **argv)
{
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    union
    {
      __sighandler_t sa_handler;
      void (*sa_sigaction) (int, siginfo_t *, void *);
    } __sigaction_handler;
    __sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  }
#endif

  memset(&act, 0, sizeof(act));

  act.sa_sigaction = signal_handler;

  sigemptyset(&act.sa_mask);

  act.sa_flags = 0;
  act.sa_flags |= SA_SIGINFO;

  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (sigaction(SIGINT, &act, &oact) < 0)
  {
    fprintf(stderr, "Install new signal handler for SIGINT failed: %s\n", strerror(errno));
  }

  for (;;)
  {
    fprintf(stdout, ".");
    fflush(stdout);

    sleep(1);
  }

  return 0;
}

void signal_handler(int signum, siginfo_t * info, void *data)
{
  struct passwd *pwd;

  //struct passwd *getpwuid(uid_t uid);
  pwd = getpwuid(info->si_uid);

  fprintf(stdout, "Caught signal %d from process %d, by %d(%s), value = %d.\n", signum, info->si_pid, info->si_uid, pwd == NULL ? "unknown" : pwd->pw_name, info->si_value.sival_int);

#if 0
  // defined in man page
  siginfo_t
  {
    int si_signo;		/* Signal number */
    int si_errno;		/* An errno value */
    int si_code;		/* Signal code */
    pid_t si_pid;		/* Sending process ID */
    uid_t si_uid;		/* Real user ID of sending process */
    int si_status;		/* Exit value or signal */
    clock_t si_utime;		/* User time consumed */
    clock_t si_stime;		/* System time consumed */
    sigval_t si_value;		/* Signal value */
    int si_int;			/* POSIX.1b signal */
    void *si_ptr;		/* POSIX.1b signal */
    void *si_addr;		/* Memory location which caused fault */
    int si_band;		/* Band event */
    int si_fd;			/* File descriptor */
  }
#endif

#if 0
  // defined in /usr/include/asm-generic/siginfo.h
  typedef struct siginfo
  {
    int si_signo;
    int si_errno;
    int si_code;

    union
    {
      int _pad[SI_PAD_SIZE];

      /* kill() */
      struct
      {
	pid_t _pid;		/* sender's pid */
	__ARCH_SI_UID_T _uid;	/* sender's uid */
      } _kill;

      /* POSIX.1b timers */
      struct
      {
	timer_t _tid;		/* timer id */
	int _overrun;		/* overrun count */
	char _pad[sizeof(__ARCH_SI_UID_T) - sizeof(int)];
	sigval_t _sigval;	/* same as below */
	int _sys_private;	/* not to be passed to user */
      } _timer;

      /* POSIX.1b signals */
      struct
      {
	pid_t _pid;		/* sender's pid */
	__ARCH_SI_UID_T _uid;	/* sender's uid */
	sigval_t _sigval;
      } _rt;

      /* SIGCHLD */
      struct
      {
	pid_t _pid;		/* which child */
	__ARCH_SI_UID_T _uid;	/* sender's uid */
	int _status;		/* exit code */
	clock_t _utime;
	clock_t _stime;
      } _sigchld;

      /* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
      struct
      {
	void *_addr;		/* faulting insn/memory ref. */
#  ifdef __ARCH_SI_TRAPNO
	int _trapno;		/* TRAP # which caused the signal */
#  endif
      } _sigfault;

      /* SIGPOLL */
      struct
      {
	__ARCH_SI_BAND_T _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
	int _fd;
      } _sigpoll;
    } _sifields;
  } siginfo_t;
#endif
}
