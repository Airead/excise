#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  mqd_t m;

  //mqd_t mq_open(const char *name, int oflag);
  if ((m = mq_open(argv[1], O_WRONLY)) == (mqd_t) - 1)
  {
    fprintf(stderr, "Open message queue for writing failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open message queue for writing successfully\n");

  unsigned int priority;

  priority = (unsigned int) strtol(argv[3], NULL, 10);

  //mqd_t mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);
  if (mq_send(m, argv[2], strlen(argv[2]), priority) < 0)
  {
    fprintf(stderr, "Send message to message queue failed: %s\n", strerror(errno));
    mq_close(m);
    exit(1);
  }

  fprintf(stdout, "Send message to message queue successfully\n");

  mq_close(m);

  return 0;
}
