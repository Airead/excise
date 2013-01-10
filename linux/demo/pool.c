/**
 * @file pool.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/05 16:24:45
 */

#include <poll.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    struct pollfd  fds;
    int retval;

    fds.fd = open("/var/log/syslog", O_RDONLY);
    if (fds.fd < 0)
    {
        perror("open()");
        return -1;
    }

    fds.events = POLLIN | POLLOUT;

    retval = poll(&fds, 1, 5000*10);
    if ( retval == 0)
        printf("timeout return\n");
    else
    {
        if (fds.revents & POLLIN)
            printf("ready to read\n");
        if (fds.revents & POLLOUT)
            printf("ready to write\n");
    }

    return 0;
}
