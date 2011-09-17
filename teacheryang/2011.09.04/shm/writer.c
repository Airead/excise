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
  if ((fd = shm_open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
  {
    if (errno == EEXIST)
    {
      if ((fd = shm_open(argv[1], O_RDWR, 0644)) < 0)
      {
	fprintf(stderr, "Open POSIX shared memory object failed: %s\n", strerror(errno));
	exit(1);
      }
    }
    else
    {
      fprintf(stderr, "Create POSIX shared memory object failed: %s\n", strerror(errno));
      exit(1);
    }
  }

  fprintf(stdout, "Create POSIX shared memory successfully, fd = %d\n", fd);

  //-------------------------------------------------------------------
  // Expend file size to required length
  //------------------------------------------------------------------
  //off_t lseek(int fildes, off_t offset, int whence);
  lseek(fd, MAPPED_SIZE, SEEK_SET);

  //ssize_t write(int fd, const void *buf, size_t count);
  write(fd, "x", 1);

  //-------------------------------------------------------------------
  // Map file to memory
  //------------------------------------------------------------------
  void *handle;

  //void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
  if ((handle = mmap(NULL, MAPPED_SIZE, PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
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
  // Update timestamp per second
  //------------------------------------------------------------------
  time_t now;
  struct tm *t;

  for (;;)
  {
    //time_t time(time_t * t);
    now = time(NULL);

#if 0
    //struct tm *gmtime(const time_t * timep);
    t = gmtime(&now);
#endif

    //struct tm *localtime(const time_t * timep);
    t = localtime(&now);

#if 0
    struct tm
    {
      int tm_sec;		/* seconds */
      int tm_min;		/* minutes */
      int tm_hour;		/* hours */
      int tm_mday;		/* day of the month */
      int tm_mon;		/* month */
      int tm_year;		/* year */
      int tm_wday;		/* day of the week */
      int tm_yday;		/* day in the year */
      int tm_isdst;		/* daylight saving time */
    };
#endif

    sem_wait(s);

    //int snprintf(char *str, size_t size, const char *format, ...);
    snprintf(handle + OFFSET, MAPPED_SIZE - OFFSET - 1, "Current time: %04d-%02d-%02d %2d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    sem_post(s);

    sleep(1);
  }

  //-------------------------------------------------------------------
  // Close & delete semaphore object
  //------------------------------------------------------------------
  sem_close(s);
  sem_unlink(argv[2]);

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

  //-------------------------------------------------------------------
  // Delete shared memory object
  //------------------------------------------------------------------
  //int shm_unlink(const char *name);
  shm_unlink(argv[1]);

  return 0;
}
