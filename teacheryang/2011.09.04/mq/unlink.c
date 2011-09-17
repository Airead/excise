#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  //mqd_t mq_unlink(const char *name);
  if (mq_unlink(argv[1]) < 0)
  {
    fprintf(stderr, "Cannot remove message queue %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Message queue %s removed.\n", argv[1]);

  return 0;
}
