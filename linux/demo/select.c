/**
 * @file select.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/24 13:55:55
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    struct timeval tv;
    fd_set readfds;
    int ret, fd;
    char buf[4096];

    fd = STDIN_FILENO;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    while (1) {
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        ret = select(fd + 1, &readfds, NULL, NULL, &tv);
        if (ret < 0) {
            if (errno != EINTR) {
                fprintf(stderr, "select failed:%s\n", strerror(errno));
                return -1;
            }
        } else if (ret == 0) {
            fprintf(stdout, "time out\n");
        } else {
            if (FD_ISSET(fd, &readfds)) {
                ret = read(fd, buf, sizeof(buf));
                buf[ret - 1] = '\0';
                fprintf(stdout, "receive %s\n", buf);
            }
        }
        FD_SET(fd, &readfds);
    }
    return 0;
}
