/**
 * @file netflow.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/03 15:14:37
 */

#ifndef _CHAT_H
#define _CHAT_H

#define CLIENT_MAX 64
#define NAME_MAX 128
#define BUFFER_LINE 100
#define MESSAGE_MAX 4096
#define GB_NUMBER (1024 * 1024 * 1024)
#define LOG_FILE "netflow.log"

#define LOG(log, fmt, args...) \
    fprintf(log, "%s " fmt, get_curtime(), ##args); fflush(log);

struct server {
    char name[NAME_MAX];
    char *ip;
    int backlog;
    time_t time;
    int listening_socket;
    unsigned int gbn;           /* GB number */
    unsigned int bn;            /* bytes number */
    FILE *log;
    unsigned short port;
    char connfd_list[CLIENT_MAX];
    char *client_names[CLIENT_MAX];
};

struct client {
    char server_ip;
    char server_port;
    char client_name[NAME_MAX];
    char messages[MESSAGE_MAX];
};

struct chat_data {
    char server_name[NAME_MAX];
    char *client_name[CLIENT_MAX]; /* user name */
    char *chat_content[BUFFER_LINE];
};

struct select_data {
    int nfds;
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;
    struct timeval timeout;
};

enum select_fdset_type {
    SELECT_DATA_READ,
    SELECT_DATA_WRITE,
    SELECT_DATA_EXCEPT
};

#endif
