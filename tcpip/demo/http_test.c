/**
 * @file http_test.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/03 15:26:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in peer_addr, self_addr;
    char *ip, *version, *req_raw, *host;
    char request[512], r_buf[512];
    socklen_t len, req_len;
    ssize_t wn, rn;
    int tr;                     /* total read bytes */

    if (argc < 5) {
        fprintf(stderr, "usage: %s <ip_addr> <http version> <request> <host>\n", argv[0]);
        exit(1);
    }

    ip = argv[1];
    version = argv[2];
    req_raw = argv[3];
    host = argv[4];

    //int socket(int domain, int type, int protocol);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("create socket failed");
        exit(1);
    }

#if 0
    struct sockaddr_in {
        sa_family_t    sin_family; /* address family: AF_INET */
        in_port_t      sin_port;   /* port in network byte order */
        struct in_addr sin_addr;   /* internet address */
    };
#endif
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(80);
    
    //int inet_pton(int af, const char *src, void *dst);
    if (inet_pton(AF_INET, ip, &peer_addr.sin_addr) < 0) {
        perror("inet_pton:");
        exit(1);
    }

    len = sizeof(peer_addr);
    //int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    if (connect(sock, (const struct sockaddr *)&peer_addr, len) < 0) {
        perror("connect failed:");
        exit(1);
    }

    //int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    if (getsockname(sock, (struct sockaddr *)&self_addr, &len) < 0) {
        perror("getsockname failed:");
        exit(1);
    }
    

    printf("connect to %s successful at %d\n", ip, ntohs(self_addr.sin_port));

    sleep(2);

    /* create request */
    memset(request, 0, sizeof(request));
    req_len = snprintf(request, sizeof(request) - 1, "GET %s %s\nHOST: %s\n\n", req_raw, version, host);
    
    printf("send request:\n%s\n", request);

    wn = write(sock, request, req_len);
    if (wn < req_len) {
        fprintf(stderr, "write %lu bytes, less than %lu: %s", wn, (unsigned long int)req_len, strerror(errno));
        exit(1);
    }
    fprintf(stdout, "write %lu bytes to server\n", wn);

    tr = 0;
    while ((rn = read(sock, r_buf, sizeof(r_buf))) != 0) {
        if (rn < 0) {
            perror("\nread error:");
            break;
        }
        tr += rn;
        write(STDOUT_FILENO, r_buf, rn);
    }

    printf("\ntotal read %d bytes\n", tr);

    close(sock);
    return 0;
}
