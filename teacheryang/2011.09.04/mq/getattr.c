#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  mqd_t m;

  //mqd_t mq_open(const char *name, int oflag);
  if ((m = mq_open(argv[1], O_RDONLY)) == (mqd_t) - 1)
  {
    fprintf(stderr, "Open message queue for reading failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open message queue for reading successfully\n");

  struct mq_attr attr;

  //mqd_t mq_getattr(mqd_t mqdes, struct mq_attr *attr);
  mq_getattr(m, &attr);

#if 0
  struct mq_attr
  {
    long mq_flags;		/* Flags: 0 or O_NONBLOCK */
    long mq_maxmsg;		/* Max. # of messages on queue */
    long mq_msgsize;		/* Max. message size (bytes) */
    long mq_curmsgs;		/* # of messages currently in queue */
  };
#endif

  fprintf(stdout, "Max message: %ld\n", attr.mq_maxmsg);
  fprintf(stdout, "Message size: %ld\n", attr.mq_msgsize);
  fprintf(stdout, "Current message: %ld\n", attr.mq_curmsgs);

  mq_close(m);

  return 0;
}
