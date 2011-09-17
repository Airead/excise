#include <stdio.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
  //int sem_unlink(const char *name);
  sem_unlink(argv[1]);
  return 0;
}
