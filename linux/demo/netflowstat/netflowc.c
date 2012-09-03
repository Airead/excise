/**
 * @file netflowc.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/03 15:14:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "netflow.h"

int get_connected_socket(char *ip, unsigned short port)
{
    int fd;
    struct sockaddr_in remote_ipv4_address;

    /* Create a socket */
    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Create new TCP socket failed: %s\n", strerror(errno));
        exit(1);
    }

    /* Connet */
    memset(&remote_ipv4_address, 0, sizeof(remote_ipv4_address));

    remote_ipv4_address.sin_family = AF_INET;
    remote_ipv4_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &remote_ipv4_address.sin_addr);

    if (connect(fd, (struct sockaddr *)&remote_ipv4_address, sizeof(remote_ipv4_address)) < 0) {
        fprintf(stderr, "Connect to remote server %s:%d failed: %s\n", ip, port, strerror(errno));
        close(fd);
        exit(1);
    }

    fprintf(stdout, "Connect to remote server %s:%d successful\n", ip, port);
    
    return fd;
}

int main(int argc, char *argv[])
{
    int fd;
    char *ip;
    unsigned short port;
    char buf[MESSAGE_MAX + 1000];
    char *p;
    char *str = 
        "GET / HTTP/1.1\r\n"
        "Host: www.yfz.com\r\n"
        "Accept-Encoding: bula bula bulala\r\n"
        "some ip : 192.168.1.air, 172.16.56.bbb\r\n"
        "SOME IP : 192.168.11.air, 172.16.55.sss\r\n"
        "1234#@$%!3456436!@#$%#$%@#^$"
        "Accept-Encoding: bula bula bulala\r\n"
        "MOUNTIAN TOP, DAY AND NIGHT\r\n"
        "HELLO HELL0 A B C D\r\n\r\n\r\n\r\n";
    

    if (argc < 3) {
        fprintf(stderr, "usage: %s <ip_addr> <port>\n", argv[0]);
        exit(1);
    }

    ip = argv[1];
    port = (unsigned short)strtol(argv[2], NULL, 10);

    if ((fd = get_connected_socket(ip, port)) < 0) {
        fprintf(stderr, "get connected socket failed: %s\n", strerror(errno));
        exit(1);
    }

    memset(buf, 0, sizeof(buf));
    p = buf;
    while (strlen(p) + strlen(str) < sizeof(buf)) {
        strcat(buf, str);
    }
    
    for (;;) {
        write(fd, buf, sizeof(buf));
    }

    close(fd);
    return 0;
}
