#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  DIR *dir;
  char *target = NULL;

  if (argc < 2)
  {
    //char *strdup(const char *s);
    target = strdup(".");
  }
  else
  {
    target = strdup(argv[1]);
  }

  if (!target)
  {
    fprintf(stderr, "Cannot compose target string.\n");
    exit(1);
  }

  // step 1, open directory stream
  //DIR *opendir(const char *name);
  if ((dir = opendir(target)) == NULL)
  {
    fprintf(stderr, "Open target directory %s failed: %s\n", target, strerror(errno));
    exit(1);
  }

  // step 2, read dirent one by one
  struct dirent *de;

#if 0
  struct dirent
  {
    ino_t d_ino;		/* inode number */
    off_t d_off;		/* offset to the next dirent */
    unsigned short d_reclen;	/* length of this record */
    unsigned char d_type;	/* type of file */
    char d_name[256];		/* filename */
  };
#endif

  // struct dirent *readdir(DIR *dir);
  while ((de = readdir(dir)))
  {
    fprintf(stdout, "%s\n", de->d_name);
  }

  // step 3, close directory stream
  closedir(dir);

  free(target);
  target = NULL;

  return 0;
}
