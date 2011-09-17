#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  struct passwd *pwd;

  //struct passwd *getpwnam(const char *name);
  pwd = getpwnam(argv[2]);

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

  struct group *grp;

  //struct group *getgrnam(const char *name);
  grp = getgrnam(argv[3]);

#if 0
  struct group
  {
    char *gr_name;		/* group name */
    char *gr_passwd;		/* group password */
    gid_t gr_gid;		/* group ID */
    char **gr_mem;		/* group members */
  };
#endif

  //int chown(const char *path, uid_t owner, gid_t group);
  //int fchown(int fd, uid_t owner, gid_t group);
  //int lchown(const char *path, uid_t owner, gid_t group);
  if (chown(argv[1], pwd->pw_uid, grp->gr_gid) < 0)
  {
    // On success, zero is returned.  On error, -1 is  returned,  and
    // errno is set appropriately.
    fprintf(stderr, "Change ownership of file %s failed: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Onwership of file %s changed to %s:%s.\n", argv[1], argv[2], argv[3]);

  return 0;
}
