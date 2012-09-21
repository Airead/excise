/**
 * @file ircrecoder.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/13 16:44:45
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
static char buf[MESSAGE_MAX + 1];


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

int ping_handler(int fd, char *buf, int len)
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

int get_line(int fd, char *buf, int buflen)
{
    char ch;
    int count;

    count = 0;
	while (1) {
		if (recv(fd, &ch, 1, 0) < 0) {
            return 0;
        }

        /* all strings end in \r\n, so look for the \n */
        if (ch == '\n') {
            buf[count] = '\0';
            if (count - 1 >= 0) {
                if(buf[count - 1] == '\r') {
                    buf[count - 1] = '\0';
                    count--;
                }
            }
            count++;
            break;
        }

        buf[count] = ch;
        count++;
    }

    /* buffer size is 1500 */
    if (count > 1500) {
        /* hmm, looks like buffer got away somewhere, 
           return an error 
        */
        fprintf(stderr, "packet > 1500\n");
        return 0;
    }

    return count;
}

int main(int argc, char *argv[])
{
    int fd;
    char *ip;
    unsigned short port;
    char *nickname;
    char *channel;
    int rn;
    char cmd[1024];

    if (argc < 5) {
        fprintf(stderr, "usage: %s <ip_addr> <port> <nickname> <channel>\n", argv[0]);
        exit(1);
    }

    ip = argv[1];
    port = (unsigned short)strtol(argv[2], NULL, 10);
    nickname = argv[3];
    channel = argv[4];

    if ((fd = get_connected_socket(ip, port)) < 0) {
        fprintf(stderr, "get connected socket failed: %s\n", strerror(errno));
        exit(1);
    }
    
    snprintf(cmd, sizeof(cmd), "NICK %s\r\n", nickname);
    write(fd, cmd, strlen(cmd));
    snprintf(cmd, sizeof(cmd), "USER %s localhost irc.freenode.net : %s\r\n", nickname, nickname);
    write(fd, cmd, strlen(cmd));

    for (;;) {
        if ((rn = get_line(fd, buf, MESSAGE_MAX + 1)) < 0) {
            break;
        }

        if (rn == 0) {
            fprintf(stdout, "remote close\n");
            break;
        }

        fprintf(stdout, "%s\n", buf);
        snprintf(cmd, sizeof(cmd), ":%s MODE %s :+i", nickname, nickname);
        if (strcmp(buf, cmd) == 0) {
            snprintf(cmd, sizeof(cmd), "JOIN #%s\r\n", channel);
            write(fd, cmd, strlen(cmd));
        } else if (strncmp(buf, "PING :", 6) == 0) {
            ping_handler(fd, buf, rn);
            write(STDOUT_FILENO, buf, rn);
        }
        
        
        memset(buf, 0, sizeof(buf));
        
    }

    close(fd);
    return 0;
}
