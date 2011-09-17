#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

#define BUFFER_SIZE	1024

void dump_file_info(char *filename, char *shortname);

int main(int argc, char **argv)
{
  DIR *dir;
  char target_directory[BUFFER_SIZE];

  if (argc < 2)
  {
    // open current directory
    //DIR *opendir(const char *name);
    dir = opendir(".");

    // void *memcpy(void *dest, const void *src, size_t n);
    memcpy(target_directory, ".", strlen("."));
  }
  else
  {
    // open user specified directory
    //DIR *opendir(const char *name);
    dir = opendir(argv[1]);

    // void *memcpy(void *dest, const void *src, size_t n);
    memcpy(target_directory, argv[1], strlen(argv[1]));
  }

  if (dir == NULL)
  {
    fprintf(stderr, "Open directory %s failed: %s\n", target_directory, strerror(errno));
    exit(1);
  }

  struct dirent *e;

  //struct dirent *readdir(DIR *dir);

  while ((e = readdir(dir)))
  {
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

    //fprintf(stdout, "%s\n", e->d_name);

    char full_filename[BUFFER_SIZE];

    // int snprintf(char *str, size_t size, const char *format, ...);
    snprintf(full_filename, sizeof(full_filename) - 1, "%s/%s", target_directory, e->d_name);

    dump_file_info(full_filename, e->d_name);
  }

  //int closedir(DIR *dir);
  closedir(dir);

  return 0;
}

void dump_file_info(char *filename, char *shortname)
{
  struct stat s;

  //------------------------------------------------------------------
  // Get file status, result stores into s
  //------------------------------------------------------------------
  //int fstat(int filedes, struct stat *buf);
  //int lstat(const char *path, struct stat *buf);
  //int stat(const char *path, struct stat *buf);
  if (stat(filename, &s) < 0)
  {
    fprintf(stderr, "Get file status for file %s failed: %s\n", filename, strerror(errno));
    exit(1);
  }

  //fprintf(stdout, "Get file status for file %s successfully.\n", filename);

  //------------------------------------------------------------------
  // struct stat definition
  //------------------------------------------------------------------
#if 0
  struct stat
  {
    dev_t st_dev;		/* ID of device containing file */
    ino_t st_ino;		/* inode number */
    mode_t st_mode;		/* protection */
    nlink_t st_nlink;		/* number of hard links */
    uid_t st_uid;		/* user ID of owner */
    gid_t st_gid;		/* group ID of owner */
    dev_t st_rdev;		/* device ID (if special file) */
    off_t st_size;		/* total size, in bytes */
    blksize_t st_blksize;	/* blocksize for filesystem I/O */
    blkcnt_t st_blocks;		/* number of blocks allocated */
    time_t st_atime;		/* time of last access */
    time_t st_mtime;		/* time of last modification */
    time_t st_ctime;		/* time of last status change */
  };
#endif

  //------------------------------------------------------------------
  // Output filename
  //------------------------------------------------------------------
  //fprintf(stdout, "  File: `%s'\n", filename);

  //------------------------------------------------------------------
  // Compose file type string
  //------------------------------------------------------------------
  int ft;

  /*
     S_IFMT     0170000   bitmask for the file type bitfields
     S_IFSOCK   0140000   socket
     S_IFLNK    0120000   symbolic link
     S_IFREG    0100000   regular file
     S_IFBLK    0060000   block device
     S_IFDIR    0040000   directory
     S_IFCHR    0020000   character device
     S_IFIFO    0010000   FIFO
   */

  ft = s.st_mode & S_IFMT;

  ft = ft >> 12;

  char *filetype_long[32];
  char filetype_short[32];

  int i;

  for (i = 0; i < 32; i++)
  {
    filetype_long[i] = NULL;
  }

  filetype_long[014] = "socket";
  filetype_long[012] = "symbolic link";
  filetype_long[010] = "regular file";
  filetype_long[006] = "block device";
  filetype_long[004] = "directory";
  filetype_long[002] = "character device";
  filetype_long[001] = "FIFO";

  memset(filetype_short, 0, sizeof(filetype_short));

  filetype_short[014] = 's';
  filetype_short[012] = 'l';
  filetype_short[010] = '-';
  filetype_short[006] = 'b';
  filetype_short[004] = 'd';
  filetype_short[002] = 'c';
  filetype_short[001] = 'p';

  //------------------------------------------------------------------
  // Output file size, blocks, block size, file type
  //------------------------------------------------------------------
  //fprintf(stdout, "  Size: %ld            Blocks: %ld          IO Block: %ld  %s\n", s.st_size, s.st_blocks, s.st_blksize, filetype_long[ft]);

#if 0
  if (S_ISREG(s.st_mode))	//  is it a regular file?
  {
    fprintf(stdout, "regular file");
  }
  else if (S_ISDIR(s.st_mode))	//  directory?
  {
    fprintf(stdout, "directory");
  }
  else if (S_ISCHR(s.st_mode))	//  character device?
  {
    fprintf(stdout, "character device");
  }
  else if (S_ISBLK(s.st_mode))	//  block device?
  {
    fprintf(stdout, "block device");
  }
  else if (S_ISFIFO(s.st_mode))	// FIFO (named pipe)?
  {
    fprintf(stdout, "named pipe");
  }
  else if (S_ISLNK(s.st_mode))	//  symbolic link? (Not in POSIX.1-1996.)
  {
    fprintf(stdout, "symbolic link");
  }
  else if (S_ISSOCK(s.st_mode))	// socket? (Not in POSIX.1-1996.)
  {
    fprintf(stdout, "socket");
  }

  fprintf(stdout, "\n");
#endif

  //------------------------------------------------------------------
  // Output device information, inode number, links cound
  //------------------------------------------------------------------
  //fprintf(stdout, "Device: N/A       Inode: %ld      Links: %d\n", s.st_ino, s.st_nlink);

  //------------------------------------------------------------------
  // Calculate permission string
  //------------------------------------------------------------------
  char permission[] = "-rwxrwxrwx";

  permission[0] = filetype_short[ft];

  //int i;
  int mode = s.st_mode;

  for (i = 0; i < 9; i++)
  {
    if ((mode & 0x01) == 0)
    {
      permission[9 - i] = '-';
    }

    mode = mode >> 1;
  }

  //S_ISUID    0004000   set UID bit
  if (s.st_mode & S_ISUID)
  {
    if (s.st_mode & S_IXUSR)
    {
      permission[3] = 's';
    }
    else
    {
      permission[3] = 'S';
    }
  }

  //S_ISGID    0002000   set-group-ID bit (see below)
  if (s.st_mode & S_ISGID)
  {
    if (s.st_mode & S_IXGRP)
    {
      permission[6] = 's';
    }
    else
    {
      permission[6] = 'S';
    }
  }

  //S_ISVTX    0001000   sticky bit (see below)
  if (s.st_mode & S_ISVTX)
  {
    if (s.st_mode & S_IXOTH)
    {
      permission[9] = 't';
    }
    else
    {
      permission[9] = 'T';
    }
  }

  //------------------------------------------------------------------
  // Get password information
  //------------------------------------------------------------------
  struct passwd *pwd;

  //struct passwd *getpwuid(uid_t uid);
  pwd = getpwuid(s.st_uid);

#if 0
  struct passwd
  {
    char *pw_name;		/* user name */
    char *pw_passwd;		/* user password */
    uid_t pw_uid;		/* user ID */
    gid_t pw_gid;		/* group ID */
    char *pw_gecos;		/* real name */
    char *pw_dir;		/* home directory */
    char *pw_shell;		/* shell program */
  };
#endif

  //------------------------------------------------------------------
  // Get group information
  //------------------------------------------------------------------
  struct group *grp;

  //struct group *getgrgid(gid_t gid);
  grp = getgrgid(s.st_gid);

#if 0
  struct group
  {
    char *gr_name;		/* group name */
    char *gr_passwd;		/* group password */
    gid_t gr_gid;		/* group ID */
    char **gr_mem;		/* group members */
  };
#endif

  //------------------------------------------------------------------
  // Output access mode, ownership
  //------------------------------------------------------------------
  //fprintf(stdout, "Access: (0%o/%s)  Uid: (  %d/     %s)   Gid: (  %d/    %s)\n", s.st_mode & 07777, permission, s.st_uid, pwd->pw_name, s.st_gid, grp->gr_name);

  //------------------------------------------------------------------
  // Output atime, mtime, ctime
  //------------------------------------------------------------------
  struct tm *tm;

  // struct tm *localtime(const time_t *timep);
  tm = localtime(&s.st_atime);

  //fprintf(stdout, "Access: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  // struct tm *localtime(const time_t *timep);
  tm = localtime(&s.st_mtime);

  //fprintf(stdout, "Modify: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

// struct tm *localtime(const time_t *timep);
  //tm = localtime(&s.st_ctime);

  //fprintf(stdout, "Change: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  fprintf(stdout, "%s %4d %8s %8s %8ld", permission, s.st_nlink, pwd->pw_name, grp->gr_name, s.st_size);

  fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  fprintf(stdout, " %s", shortname);

  fprintf(stdout, "\n");
}

// vim:tabstop=8
