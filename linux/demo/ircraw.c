/**
 * @file ircraw.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/11 14:50:08
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

#define MESSAGE_MAX 4096

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

static int ping_handler(int fd, char *buf, int len)
{
    char *cmd;
    char *server;

    cmd = strtok(buf, ":");
    server = strtok(NULL, ":");
    if (server) {
        write(fd, server, server - cmd);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int fd, ret;
    char *ip;
    unsigned short port;
    ssize_t rn;
    char cmd[1024];
    char buf[MESSAGE_MAX + 1];
    
    struct timeval to;          /* timeout */
    fd_set readfds;

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
    
    snprintf(cmd, sizeof(cmd), "NICK aaiiread\r\n");
    write(fd, cmd, strlen(cmd));
    snprintf(cmd, sizeof(cmd), "USER aaiiread localhost irc.freenode.net : aaiiread\r\n");
    write(fd, cmd, strlen(cmd));

    FD_ZERO(&readfds);
 
    for (;;) {
        to.tv_sec = 60;
        to.tv_usec = 0;
        FD_SET(fd, &readfds);
        FD_SET(STDOUT_FILENO, &readfds);

        ret = select(fd + 1, &readfds, NULL, NULL, &to);
        
        if (ret < 0) {
            fprintf(stderr, "select error\n");
        } else if (ret == 0) {
//            fprintf(stderr, "time out...\n");
            snprintf(cmd, sizeof(cmd), "PING irc.freenode.net\r\n");
            write(fd, cmd, strlen(cmd));
        } else {
            if (FD_ISSET(fd, &readfds)) {
//                fprintf(stdout, "readable\n");
                if ((rn = read(fd, buf, MESSAGE_MAX)) < 0) {
                    perror("read error");
                    break;
                }
                if (rn > 6) {
                    if (strncmp(buf, "PING :", 6) == 0) {
                        ping_handler(fd, buf, rn);
                    }
                }
                write(STDOUT_FILENO, buf, rn);
            }

            if (FD_ISSET(STDOUT_FILENO, &readfds)) {
//                fprintf(stdout, "can read\n");
                memset(buf, 0, sizeof(buf));
                read(STDOUT_FILENO, buf, MESSAGE_MAX);
                write(fd, buf, MESSAGE_MAX);
            }
        }
    }

    close(fd);
    return 0;
}
