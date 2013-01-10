/**
 * @file dup2.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/06 15:42:37
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    fd = open("dup2.log", O_WRONLY | O_APPEND | O_CREAT, 0660);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open relay file %s: errcode = %s\n",
                "dup2.log", strerror(errno));
        return -1;
    }

    dup2(fd, STDOUT_FILENO);
    
    fprintf(stdout, "hello, this \n");

    return 0;
}
