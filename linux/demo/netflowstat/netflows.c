/**
 * @file netflows.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/03 15:14:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#include "netflow.h"

static char curtime[200];

static char *get_curtime(void)
{
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        perror("localtime");
        return "null";
    }

    if (strftime(curtime, sizeof(curtime), "%Y/%m/%d %H:%M:%S", tmp) == 0) {
        fprintf(stderr, "strftime returned 0");
        return "null";
    }

    return curtime;
}

/**
 * get listen socket
 */
static int get_listen_socket(char *ip, unsigned short port, int listen_backlog)
{
    int listening_socket;
    int optval;
    struct sockaddr_in local_ipv4_address;

    /* Create a socket */
    //int socket(int domain, int type, int protocol);
    if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Failed to create new TCP socket: %s\n", strerror(errno));
        return -1;
    }

    /* set socket option */
    optval = 1;
    //int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

#ifdef SO_REUSEPORT
    optval = 1;
    setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

    /* bind */
    memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

    local_ipv4_address.sin_family = AF_INET;
    local_ipv4_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &local_ipv4_address.sin_addr);

    if (bind(listening_socket, (struct sockaddr *)&local_ipv4_address, sizeof(local_ipv4_address)) < 0) {
        fprintf(stderr, "Bind to %s:%d failed: %s\n", ip, port, strerror(errno));
        close(listening_socket);
        return -1;
    }

    fprintf(stdout, "Bound to %s:%d successfully.\n", ip, port);

    /* Listen */
    if (listen(listening_socket, listen_backlog) < 0) {
        fprintf(stderr, "Listen on %s:%d failed: %s\n", ip, port, strerror(errno));
        close(listening_socket);
        return -1;
    }

    fprintf(stdout, "Listen on %s:%d successfully, waiting for incoming connections ...\n", ip, port);

    return listening_socket;
}

int select_data_set_timeout(struct select_data *sdata, int sec, int usec)
{
    sdata->timeout.tv_sec = sec;
    sdata->timeout.tv_usec = usec;

    return 0;
}

int select_data_init(struct select_data *sdata)
{
    if (sdata == NULL) {
        fprintf(stderr, "sdata is NULL!\n");
        return -1;
    }

    FD_ZERO(&sdata->readfds);
    FD_ZERO(&sdata->writefds);
    FD_ZERO(&sdata->exceptfds);

    sdata->nfds = 0;

    select_data_set_timeout(sdata, 0, 0);

    return 0;
}

int select_data_register_fdset(struct select_data *sdata, int fd, enum select_fdset_type type)
{
    if (sdata == NULL) {
        fprintf(stderr, "sdata is NULL!\n");
        return -1;
    }

    switch (type) {
    case SELECT_DATA_READ:
        FD_SET(fd, &sdata->readfds);
        break;
    case SELECT_DATA_WRITE:
        FD_SET(fd, &sdata->writefds);
        break;
    case SELECT_DATA_EXCEPT:
        FD_SET(fd, &sdata->exceptfds);
        break;
    default:
        fprintf(stderr, "select data register fd type error\n");
        return -1;
    }

    if (sdata->nfds <= fd) {
        sdata->nfds = fd + 1;
    }

    return 0;
}

int select_data_unregister_fdset(struct select_data *sdata, int fd, enum select_fdset_type type)
{
    if (sdata == NULL) {
        fprintf(stderr, "sdata is NULL!\n");
        return -1;
    }

    switch (type) {
    case SELECT_DATA_READ:
        FD_CLR(fd, &sdata->readfds);
        break;
    case SELECT_DATA_WRITE:
        FD_CLR(fd, &sdata->writefds);
        break;
    case SELECT_DATA_EXCEPT:
        FD_CLR(fd, &sdata->exceptfds);
        break;
    default:
        fprintf(stderr, "select data register fd type error\n");
    }

    return 0;
}

int select_data_select(struct select_data *sdata)
{
    int ret;

    if (sdata == NULL) {
        fprintf(stderr, "sdata is NULL!\n");
        return -1;
    }

    ret = select(sdata->nfds, &sdata->readfds, &sdata->writefds, 
                 &sdata->exceptfds, &sdata->timeout);

    return ret;
}

/** 
 * Main deal function
 */
int select_deal(struct select_data *sdata, struct server *server)
{
    int connfd;
    int i;
    char buf[MESSAGE_MAX];
    time_t secs;
    ssize_t rn;

    for (i = 0; i < sdata->nfds; i++) {
        if (FD_ISSET(i, &sdata->readfds)) {
            if (i == server->listening_socket) { /* listen socket can read --> accept */
                fprintf(stdout, "accept %d\n", i);
                connfd = accept(i, NULL, NULL);
                if (connfd < 0) {
                    fprintf(stderr, "accept failed: %s\n", strerror(errno));
                    return -1;
                }
                fprintf(stdout, "accept successful: connfd is %d\n", connfd);
                LOG(server->log, "accept successful: connfd is %d\n", connfd);
                server->connfd_list[connfd] = 1;
            } else {            /* not listen socket can read --> read and write */
//                fprintf(stdout, "socket %d is ready to read.\n", i);
                if ((rn = read(i, buf, MESSAGE_MAX)) < 0) { /* read error */
                    fprintf(stderr, "read error\n");
                    return -1;
                } else if (rn == 0) { /* 0 represent remote have closed */
                    fprintf(stdout, "remote [%d] closed\n", i);
                    LOG(server->log, "remote [%d] closed\n", i);
                    close(i);
                    server->connfd_list[i] = 0;
                } else {        /* write */
                    if (server->time == 0) {
                        server->time = time(NULL);
                    }
                    server->bn += rn;
                    if (server->bn >= GB_NUMBER) {
                        secs = time(NULL) - server->time;
                        server->time = 0;
                        server->bn -= GB_NUMBER;
                        server->gbn += 1;
                        fprintf(stdout, "current receive %u GB, during %lu seconds, %.2fM/s\n", 
                                server->gbn, secs, 1024 * 8.0 / secs);
                        LOG(server->log, "current receive %u GB, during %lu seconds, %.2fM/s\n", 
                                server->gbn, secs, 1024 * 8.0 / secs);
                    }
                }
            }
        }

        if (FD_ISSET(i, &sdata->writefds)) {
            fprintf(stdout, "socket %d is ready to write.\n", i);
        }

        if (FD_ISSET(i, &sdata->exceptfds)) {
            fprintf(stdout, "socket %d is except.\n", i);
        }
    }

    return 0;
}

/**
 * initialize struct server, include listen socket
 */
int server_init(struct server *server, char *ip, unsigned short port, 
                int backlog, char *log_file)
{
    memset(server, 0, sizeof(struct server));

    server->log = fopen(log_file, "a");
    if (server->log == NULL) {
        fprintf(stderr, "open %s failed: %s\n", log_file, strerror(errno));
        return -1;
    }

    strncpy(server->name, ip, NAME_MAX);
    server->ip = ip;
    server->port = port;
    server->backlog = backlog;

    server->listening_socket = get_listen_socket(ip, port, backlog);
    if (server->listening_socket < 0) {
        fprintf(stderr, "get listen socket failed\n");
        return -1;
    }

    server->connfd_list[server->listening_socket] = 1;

    return 0;
}

int server_show_client(struct server *server)
{
    int i;

    fprintf(stdout, "have client: ");

    for (i = 0; i < CLIENT_MAX; i++) {
        if (server->connfd_list[i] != 0) {
            fprintf(stdout, "%d, ", i);
        }
    }

    fprintf(stdout, "\n");

    return 0;
}

/**
 * Once run select, the parameters passed to select may be have changed, so we
 * should add them to watch again.
 */
int select_data_update_fdset(struct select_data *sdata, struct server *server)
{
    int i;

    for (i = 0; i < CLIENT_MAX; i++) {
        if (server->connfd_list[i] != 0) {
            select_data_register_fdset(sdata, i, SELECT_DATA_READ);
        } else {
            select_data_unregister_fdset(sdata, i, SELECT_DATA_READ);
        }
    }

    return 0;
}

/*
 * arguments: ip, port, backlog
 */
int main(int argc, char *argv[])
{
    struct server server;
    char *ip;
    unsigned short port;
    int backlog;
    struct select_data sdata, sdata_tmp;
    int select_ret;
    int count;
    
    if (argc < 3) {
        fprintf(stderr, "usage: %s <ip_addr> <port>\n", argv[0]);
        exit(1);
    }

    ip = argv[1];
    port = (unsigned short)strtol(argv[2], NULL, 10);
//    backlog = (int)strtol(argv[3], NULL, 10);
    backlog = 10;

    select_data_init(&sdata);

    if (server_init(&server, ip, port, backlog, LOG_FILE) < 0) {
        fprintf(stderr, "server initialize failed\n");
        exit(1);
    }
    LOG(server.log, "Listen on %s:%d successfully, waiting for incoming connections ...\n", 
        server.ip, server.port);

    select_data_register_fdset(&sdata, server.listening_socket, SELECT_DATA_READ);
    
    count = 0;

    /* ready to accept */
    for (;;) {
        sdata_tmp = sdata;
        select_data_set_timeout(&sdata_tmp, 2, 0);
        //int select(int nfds, fd_set *readfds, fd_set *writefds, 
        //           fd_set *exceptfds, struct timeval *timeout);
        select_ret = select_data_select(&sdata_tmp);

        if (select_ret < 0) {
            fprintf(stderr, "select() failed: %s\n", strerror(errno));
            break;
        } else if (select_ret == 0) {
            fprintf(stdout, "timeout ...\t");
            fprintf(stdout, "do something [%d]\n", count++);
        } else {
            select_deal(&sdata_tmp, &server);
        }

//        server_show_client(&server);
        select_data_update_fdset(&sdata, &server);
    }

    close(server.listening_socket);

    return 0;
}
