/**
 * @file read.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/05 14:28:39
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 16

int main(int argc, char *argv[])
{
    ssize_t rn;
    int fd;
    char *fn;
    char buf[BUF_SIZE];

    if (argc < 2) {
        fprintf(stderr, "uasge: %s <file_name>\n", argv[0]);
        exit(1);
    }
    fn = argv[1];

    // int open(const char *pathname, int flags);
    if ((fd = open(fn, O_RDONLY)) < 0) {
        fprintf(stderr, "open %s failed: %s\n", fn, strerror(errno));
        exit(1);
    }

    // ssize_t read(int fd, void *buf, size_t count);
    while ((rn = read(fd, buf, BUF_SIZE)) != 0) {
        fprintf(stdout, "read bytes: %lu\n", rn);
        // ssize_t write(int fd, const void *buf, size_t count);
        write(STDOUT_FILENO, buf, rn);
    }
    return 0;
}
