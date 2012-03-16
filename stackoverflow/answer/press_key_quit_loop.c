/**
 * @file press_key_quit_loop.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/16 12:28:52
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    fd_set readfds;
    struct timeval tv;
    int ch;
    int bool, ret;

    FD_ZERO(&readfds);
    bool = 1;
    while (bool) {
        FD_SET(STDIN_FILENO, &readfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        /* int select(int nfds, fd_set *readfds, fd_set *writefds,
         *           fd_set *exceptfds, struct timeval *timeout);         */
        ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        if (ret < 0) {
            perror("select error");
            exit(1);
        } else if (ret == 0) {
            /* timeout */
        } else if (FD_ISSET(STDIN_FILENO, &readfds)) {
            ch = fgetc(stdin);
            if (ch == 'q') {
                bool = 0;
            }
        }
        sleep(1);
        fprintf(stderr, ".");
    }
    
    return 0;
}
