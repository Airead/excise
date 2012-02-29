#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

static int is_directory(char *path)
{
    int bool;
    struct stat stat;

    bool = 0;

    //int lstat(const char *path, struct stat *buf);
    if (lstat(path, &stat) < 0) {
        fprintf(stderr, "lstat %s failed:%s \n", path, strerror(errno));
        return 0;
    }

    if (S_ISDIR(stat.st_mode)) { /* directory */
        bool = 1;
    }
    
    return bool;
}

int get_directorys(char *path, char **dirs)
{
    DIR *dirp;
    struct dirent *direntp;
    int len;
    char **dirs_tmp;
    char *subpath;

    if (is_directory(path) == 0) { /* not directory */
        fprintf(stderr, "%s is no a directory\n", path);
        return -1;
    }
    
    //DIR *opendir(const char *name);
    if ((dirp = opendir(path)) == NULL) {
        fprintf(stderr, "opendir failed:%s\n", strerror(errno));
        return -1;
    }
    
    dirs_tmp = dirs;
    //struct dirent *readdir(DIR *dirp);
    while ((direntp = readdir(dirp)) != NULL) {
        if (strcmp(direntp->d_name, ".") == 0 
            || strcmp(direntp->d_name, "..") == 0) {
            continue;
        }
        len = strlen(path) + strlen(direntp->d_name) + 1 + 1; /* "/" + "\0" */
        subpath = (char *)malloc(sizeof(char) * len);
        //int snprintf(char *str, size_t size, const char *format, ...);
        snprintf(subpath, len, "%s/%s", path, direntp->d_name);
        subpath[len -1] = '\0';
        if (is_directory(subpath) != 0) {
            *dirs_tmp++ = subpath;
        }
    }
    *dirs_tmp = NULL;

    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    char *path;
    char *dirs[512];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <starting-pathname>\n", argv[0]);
        exit(1);
    }
    path = argv[1];

    if (get_directorys(path, dirs) < 0) {
        fprintf(stderr, "get directorys failed\n");
        exit(1);
    }

    for (i = 0; dirs[i] != NULL; i++) {
        fprintf(stdout, "[%d] %s\n", i, dirs[i]);
    }

    return 0;
}
