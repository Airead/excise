#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define MAPPED_LENGTH	1024

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  //int open(const char *pathname, int flags, mode_t mode);
  if ((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
  {
    fprintf(stderr, "Open file %s for r/w failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open file %s for r/w successfully.\n", argv[1]);

  //off_t lseek(int fd, off_t offset, int whence);
  lseek(fd, MAPPED_LENGTH - 1, SEEK_SET);

  //ssize_t write(int fd, const void *buf, size_t count);
  write(fd, "x", 1);

  void *addr;

  // On  success,  mmap() returns a pointer to the mapped area.  On error, the
  // value MAP_FAILED (that is, (void *) -1) is returned,  and  errno  is  set
  // appropriately.

  //void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
  if ((addr = mmap(NULL, MAPPED_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
  {
    fprintf(stderr, "Map failed: %s\n", strerror(errno));
    close(fd);
    exit(1);
  }

  fprintf(stdout, "Map success, address: 0x%08x\n", (int) addr);

  time_t now;

  now = time(NULL);

  *((time_t *) (addr + 100)) = now;

  char message[] = "Hello world!\n";

  // WRONG: addr+200 = "hello world!\n";

  // void *memcpy(void *dest, const void *src, size_t n);
  memcpy(addr + 200, message, strlen(message));

  //int munmap(void *addr, size_t length);
  if (munmap(addr, MAPPED_LENGTH) < 0)
  {
    fprintf(stderr, "Unmap failed: %s\n", strerror(errno));
    close(fd);
    exit(1);
  }

  close(fd);

  return 0;
}
