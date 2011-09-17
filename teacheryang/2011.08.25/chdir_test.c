#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

void print_cwd(void)
{
  char buffer[BUFFER_SIZE];

  memset(buffer, 0, sizeof(buffer));

  //char *getcwd(char *buf, size_t size);
  if (getcwd(buffer, sizeof(buffer) - 1) == NULL)
  {
    if (errno == ERANGE)
    {
      fprintf(stderr, "Buffer is not enough to save pathname, increase buffer size please.\n");
      exit(1);
    }

    fprintf(stderr, "Cannot get CWD: %s\n", strerror(errno));
  }

  fprintf(stdout, "CWD: %s\n", buffer);
}

int main(int argc, char **argv)
{
  print_cwd();

  //int chdir(const char *path);
  if (chdir("/tmp") < 0)
  {
    fprintf(stderr, "Change CWD to \"/tmp\" failed: %s\n", strerror(errno));
    exit(1);
  }

  print_cwd();

  return 0;
}
