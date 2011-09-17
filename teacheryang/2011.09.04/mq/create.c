#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  struct rlimit rlim;

#if 0
  struct rlimit
  {
    rlim_t rlim_cur;		/* Soft limit */
    rlim_t rlim_max;		/* Hard limit (ceiling for rlim_cur) */
  };
#endif

  //bytes = attr.mq_maxmsg * sizeof(struct msg_msg *) + attr.mq_maxmsg * attr.mq_msgsize;
  int bytes = 100 * sizeof(struct msg_msg *) + 100 * 8192;

  rlim.rlim_cur = bytes;
  rlim.rlim_max = bytes;

  //int setrlimit(int resource, const struct rlimit *rlim);
  if (setrlimit(RLIMIT_MSGQUEUE, &rlim) < 0)
  {
    fprintf(stderr, "Change resource limit of RLIMIT_MSGQUEUE failed: %s\n", strerror(errno));
  }
  else
  {
    fprintf(stdout, "Change resource limit of RLIMIT_MSGQUEUE successfully, new value: %d\n", bytes);
  }

#if 0
  int i;

  for (i = 90; i < 100; i++)
  {
    int bytes = i * sizeof(struct msg_msg *) + i * 8192;

    fprintf(stdout, "%d, bytes = %d\n", i, bytes);
  }
#endif

  mqd_t m;
  struct mq_attr attr;

#if 0
  struct mq_attr
  {
    long mq_flags;		/* Flags: 0 or O_NONBLOCK */
    long mq_maxmsg;		/* Max. # of messages on queue */
    long mq_msgsize;		/* Max. message size (bytes) */
    long mq_curmsgs;		/* # of messages currently in queue */
  };
#endif

  memset(&attr, 0, sizeof(attr));

  // default value is 10, if required, modify /proc/sys/fs/mqueue/msg_max to increase the value
  attr.mq_maxmsg = 99;

  // default value is 8192, if required, modify /proc/sys/fs/mqueue/msgsize_max to increase the value
  attr.mq_msgsize = 8192;

  //mqd_t mq_open(const char *name, int oflag);
  //mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
  m = mq_open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644, &attr);

  if (m == (mqd_t) - 1)
  {
    fprintf(stderr, "Create new POSIX Message queue failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Create new POSIX Message queue successfully.\n");

  mq_close(m);

  return 0;
}
