/**
 * @file getmac2.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/17 11:05:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for strncpy */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

#ifndef ERR_LIB
        void perr_quit(char *x){
                perror(x);
                exit(1);
        }
#endif

int main(void)
{
        int     x = 0, sock = 0;
        struct ifreq ifreq;

        //make a socket
        if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                perr_quit("socket");

        //loop thru indices starting at 1, print each one out
        //quit on a bad one
        for(x = 1; x < 10; x++){
                ifreq.ifr_ifindex = x;
                if(ioctl(sock, SIOCGIFNAME, &ifreq) < 0 )
                        perr_quit("ioctl");
                printf("index %d is %s\n", x, ifreq.ifr_name);
        }

        return 0;
}
