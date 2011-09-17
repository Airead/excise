#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>		/* For O_* constants */
#include <time.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define MAPPED_SIZE	1024
#define OFFSET		100

//--------------------------------------------------------------------
// Function implementation
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int fd;

  //-------------------------------------------------------------------
  // Create/Open shared memory object
  //------------------------------------------------------------------
  //int shm_open(const char *name, int oflag, mode_t mode);
  if ((fd = shm_open(argv[1], O_RDONLY, 0644)) < 0)
  {
    fprintf(stderr, "Open POSIX shared memory object failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open POSIX shared memory successfully, fd = %d\n", fd);

  //-------------------------------------------------------------------
  // Map file to memory
  //------------------------------------------------------------------
  void *handle;

  //void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
  if ((handle = mmap(NULL, MAPPED_SIZE, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
  {
    fprintf(stderr, "Map failed: %s\n", strerror(errno));
    close(fd);
    shm_unlink(argv[1]);
    exit(1);
  }

  fprintf(stdout, "Created a shared memory at 0x%08lx, size = %d bytes.\n", (unsigned long) handle, MAPPED_SIZE);

  //-------------------------------------------------------------------
  // Create/Open semaphore object
  //------------------------------------------------------------------
  sem_t *s;

  //sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
  if ((s = sem_open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
  {
    if (errno == EEXIST)
    {
      if ((s = sem_open(argv[2], O_RDWR)) == SEM_FAILED)
      {
	fprintf(stderr, "Create semaphore failed: %s\n", strerror(errno));
	// FIXME: give up?
	exit(1);
      }
    }
    else
    {
      fprintf(stderr, "Create semaphore failed: %s\n", strerror(errno));
      // FIXME: give up?
      exit(1);
    }
  }

  //-------------------------------------------------------------------
  // Read timestamp when necessary
  //------------------------------------------------------------------
  sem_wait(s);
  fprintf(stdout, "%s\n", (char *) (handle + OFFSET));
  sem_post(s);

  //-------------------------------------------------------------------
  // Close semaphore object
  //------------------------------------------------------------------
  sem_close(s);

  //-------------------------------------------------------------------
  // Unmap 
  //------------------------------------------------------------------
  //int munmap(void *start, size_t length);
  if (munmap(handle, MAPPED_SIZE) < 0)
  {
    fprintf(stderr, "munmap() failed: %s\n", strerror(errno));
    close(fd);
    shm_unlink(argv[1]);
    exit(1);
  }

  //-------------------------------------------------------------------
  // Close shared memory object
  //------------------------------------------------------------------
  close(fd);

  return 0;
}
