/**
 * @file epoll_echo.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/05/11 15:38:25
 */

#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define MAX_EVENTS 500

typedef struct myevent_s {
    int fd;
    void (*call_back)(int fd, int events, void *arg);
    int events;
    void *arg;
    int status;                 /* 1: in epoll wait list, 0 not in */
    char buff[128];             /* recv data buffer */
    int len;
    long last_active;            /* last active time */
}myevent_s;

/* set event */
void event_set(myevent_s *ev, int fd, void (*call_back)(int, int, void*), void *arg)
{
    ev->fd = fd;
    ev->call_back = call_back;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 0;
    ev->last_active = time(NULL);
}

/* add/mod an event to epoll */
void event_add(int epollFd, int events, myevent_s *ev)
{
#if 0
    struct epoll_event {
        uint32_t     events;      /* Epoll events */
        epoll_data_t data;        /* User data variable */
    };
#endif
    struct epoll_event epv = {0, {0}};
    int op;

    epv.data.ptr = ev;
    ev->events = events;
    epv.events = ev->events;

    if (ev->status == 1) {
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }
    if (epoll_ctl(epollFd, op, ev->fd, &epv) < 0) {
        printf("Event Add failed[fd=%d]\n", ev->fd);
    } else {
        printf("Event Add OK[fd=%d]\n", ev->fd);
    }
}

/* delete an event from epoll */
void event_del(int epollFd, myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};

    if (ev->status != 1)
        return;

    epv.data.ptr = ev;
    ev->status = 0;
    epoll_ctl(epollFd, EPOLL_CTL_DEL, ev->fd, &epv);
}

int g_epollFd;
myevent_s g_events[MAX_EVENTS + 1]; /* g_events[MAX_EVENTS] is used by listen fd */

void recv_data(int fd, int events, void *arg);
void send_data(int fd, int events, void *arg);

/* accept new connections from clients */
void accept_conn(int fd, int events, void *arg)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(struct sockaddr_in);
    int nfd, i;

    /* accept */
    if ((nfd = accept(fd, (struct sockaddr*)&sin, &len)) == -1) {
        if (errno != EAGAIN && errno != EINTR) {
            printf("%s: bad accept", __func__);
        }
        return ;
    }
    
    do {
        for (i = 0; i < MAX_EVENTS; i++) { /* check free events */
            if (g_events[i].status == 0) {
                break;
            }
        }
        if (i == MAX_EVENTS) {
            printf("%s: max connection limit[%d].", __func__, MAX_EVENTS);
            break;
        } 

        /* set nonblocking */
        if (fcntl(nfd, F_SETFL, O_NONBLOCK) < 0)
            break;

        /* add a read event for receive data */
        event_set(&g_events[i], nfd, recv_data, &g_events[i]);
        event_add(g_epollFd, EPOLLIN | EPOLLET, &g_events[i]);
        printf("new conn[%s:%d] [time:%ld]\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), g_events[i].last_active);
    } while (0);
}

/* recv_data */
void recv_data(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    int len;

    /* receive data */
    len = recv(fd, ev->buff, sizeof(ev->buff) - 1, 0);
    event_del(g_epollFd, ev);
    if (len > 0) {
        ev->len = len;
        ev->buff[len] = '\0';
        printf("C[%d]: %s\n", fd, ev->buff);

        /* change to send event */
        event_set(ev, fd, send_data, ev);
        event_add(g_epollFd, EPOLLOUT | EPOLLET, ev); 
    } else if (len == 0) {
        close(ev->fd);
        printf("[fd=%d] closed gracefully.\n", fd);
    } else {
        close(ev->fd);
        printf("recv[fd=%d] error[%d]: %s\n", fd, errno, strerror(errno));
    }


}

/* send data */
void send_data(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s*)arg;
    int len;

    /* send data */
    len = send(fd, ev->buff, ev->len, 0);
    ev->len = 0;
    event_del(g_epollFd, ev);
    if (len > 0) {
        /* change to receive event */
        event_set(ev, fd, recv_data, ev);
        event_add(g_epollFd, EPOLLIN | EPOLLET, ev);
    } else {
        close(ev->fd);
        printf("recv[fd=%d] error[%d]\n", fd, errno);
    }
}

void init_listen_socket(int epollFd, short port)
{
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);

    fcntl(listenFd, F_SETFL, O_NONBLOCK); /* set non-blocking */
    printf("server listen fd=%d\n", listenFd);
    event_set(&g_events[MAX_EVENTS], listenFd, accept_conn, &g_events[MAX_EVENTS]);

    /* add listen socket */
    event_add(epollFd, EPOLLIN | EPOLLET, &g_events[MAX_EVENTS]);

    /* bind & listen */
    struct sockaddr_in sin;
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    if (bind(listenFd, (const struct sockaddr *)&sin, sizeof(sin)) < 0) {
        printf("bind error: %s\n", strerror(errno));
    }
    listen(listenFd, 5);
}

int main(int argc, char **argv)
{
    short port = 12345;         /* default port */
    if (argc == 2) {
        port = atoi(argv[1]);
    }

    /* create epoll */
    g_epollFd = epoll_create(MAX_EVENTS);
    if (g_epollFd <= 0) {
        printf("create epoll failed. %d\n", g_epollFd);
    }
    /* create & bind listen socket, and add to epoll, set non-blocking */
    init_listen_socket(g_epollFd, port);
    printf("server running:port[%d]\n", port);

    /* event loop */
    struct epoll_event events[MAX_EVENTS];
    int checkPos = 0;
    while (1) {
        /* a simple timeout check here, every time 100, better to use a
         * miniheap, and add time event */
        long now = time(NULL);
        int i;
        
        for (i = 0; i < 100; i++, checkPos++) { /* doesn't check listen fd */
            if (checkPos == MAX_EVENTS) {
                checkPos = 0; //recycle
            }
            if (g_events[checkPos].status != 1) {
                continue;
            }
            long duration = now - g_events[checkPos].last_active;
            if (duration >= 10) { /* 60s timeout */
                close(g_events[checkPos].fd);
                printf("[fd=%d timeout[%ld--%ld]\n", g_events[checkPos].fd, g_events[checkPos].last_active, now);
                event_del(g_epollFd, &g_events[checkPos]);
            }
        }
        
        /* wait for events to happen */
        int fds = epoll_wait(g_epollFd, events, MAX_EVENTS, 1000);
        if (fds < 0) {
            printf("epoll_wait error, exit\n");
            break;
        }
        for (i = 0; i < fds; i++) {
            myevent_s *ev = (struct myevent_s *)events[i].data.ptr;

            if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN)) { /* read event */
                ev->call_back(ev->fd, events[i].events, ev->arg);
            }
            if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT)) { /* write event */
                ev->call_back(ev->fd, events[i].events, ev->arg);
            }
            
        }
    }
    /* free resource */
    return 0;
}



