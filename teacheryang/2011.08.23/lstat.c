#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char *file_type_string[] = {
  NULL,
  "FIFO",
  "character device",
  NULL,
  "directory",
  NULL,
  "block device",
  NULL,
  "regular file",
  NULL,
  "symbolic link",
  NULL,
  "socket",
  NULL
};

char file_type[] = "?pc?d?b?-?l?s";

int main(int argc, char **argv)
{
  struct stat s;

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
    blksize_t st_blksize;	/* blocksize for file system I/O */
    blkcnt_t st_blocks;		/* number of 512B blocks allocated */
    time_t st_atime;		/* time of last access */
    time_t st_mtime;		/* time of last modification */
    time_t st_ctime;		/* time of last status change */
  };
#endif

  //int fstat(int fd, struct stat *buf);
  //int stat(const char *path, struct stat *buf);
  //int lstat(const char *path, struct stat *buf);
  if (lstat(argv[1], &s) < 0)
  {
    // On error, -1 is returned, and errno is set appropriately.
    fprintf(stderr, "Cannot get file information: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "  File: `%s'\n", argv[1]);
  fprintf(stdout, "  Size: %d	Blocks: %d          IO Block: %d   %s\n", (int) s.st_size, (int) s.st_blocks, (int) s.st_blksize, file_type_string[(s.st_mode & S_IFMT) >> 12]);

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

  fprintf(stdout, "Device: ?/?	Inode: %d      Links: %d\n", (int) s.st_ino, (int) s.st_nlink);

  struct passwd *pwd;

  //struct passwd *getpwuid(uid_t uid);
  pwd = getpwuid(s.st_uid);

#if 0
  struct passwd
  {
    char *pw_name;		/* username */
    char *pw_passwd;		/* user password */
    uid_t pw_uid;		/* user ID */
    gid_t pw_gid;		/* group ID */
    char *pw_gecos;		/* real name */
    char *pw_dir;		/* home directory */
    char *pw_shell;		/* shell program */
  };
#endif

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

  char permission[] = "-rwxrwxrwx";

  int i;

  for (i = 0; i < 9; i++)
  {
    if (((s.st_mode >> i) & 0x01) == 0)
    {
      permission[9 - i] = '-';
    }
  }

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

  permission[0] = file_type[(s.st_mode & S_IFMT) >> 12];

  fprintf(stdout, "Access: (0%04o/%s)  Uid: ( %d/%s)   Gid: ( %d/%s)\n", s.st_mode & 07777, permission, s.st_uid, pwd->pw_name, s.st_gid, grp->gr_name);

  struct tm *tm;

  //struct tm *localtime(const time_t *timep);
  tm = localtime(&s.st_atime);

  //Access: 2011-08-22 09:14:00.000000000 +0800
  fprintf(stdout, "Access: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  //struct tm *localtime(const time_t *timep);
  tm = localtime(&s.st_mtime);

  //Modify: 2011-08-22 09:14:00.000000000 +0800
  fprintf(stdout, "Modify: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  //struct tm *localtime(const time_t *timep);
  tm = localtime(&s.st_ctime);

  //Change: 2011-08-22 09:14:00.000000000 +0800
  fprintf(stdout, "Change: %04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

  return 0;
}
