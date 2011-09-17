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

  int length = attr.mq_msgsize + 1;

  char *buffer = NULL;

  if ((buffer = (char *) malloc(length)) == NULL)
  {
    fprintf(stderr, "Allocate memory failed.\n");
    exit(1);
  }

  memset(buffer, 0, length);

  unsigned int priority;
  int n;

  //mqd_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio);
  if ((n = mq_receive(m, buffer, length, &priority)) < 0)
  {
    fprintf(stderr, "Receive message from message queue failed: %s\n", strerror(errno));

    free(buffer);
    buffer = NULL;

    mq_close(m);
    exit(1);
  }

  fprintf(stdout, "Received a message from message queue, priority = %d, length = %d: %s\n", priority, n, buffer);

  mq_close(m);

  free(buffer);
  buffer = NULL;

  return 0;
}
