#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int main(int argc, char **argv)
{
#if 0
  char *arguments[] = {
    "/bin/ls",
    "-l",
    "-a",
    "-h",
    NULL
  };

  //int execve(const char *filename, char *const argv[], char *const envp[]);
  if (execve("/bin/ls", arguments, environ) < 0)
  {
    fprintf(stderr, "Execute '/bin/ls' failed: %s\n", strerror(errno));
    exit(1);
  }
#endif

#if 0
  // WRONG: char *v[] = {"x", "y", "z", NULL};
  // WRONG: char *v[] = {"./print_args", "x", "y", "z"};
  char *v[] = { "./print_args", "x", "y", "z", NULL };

  //int execve(const char *filename, char *const argv[], char *const envp[]);
  if (execve("./print_args", v, environ) < 0)
  {
    fprintf(stderr, "Execute './print_args' failed: %s\n", strerror(errno));
    exit(1);
  }
#endif

  char *v[] = { "./print_env", NULL };
  char *e[] = { "HOME=/abc", "TERM=xxx", NULL };

  //int execve(const char *filename, char *const argv[], char *const envp[]);
  if (execve("./print_env", v, e) < 0)
  {
    fprintf(stderr, "Execute './print_env' failed: %s\n", strerror(errno));
    exit(1);
  }

  return 0;
}
