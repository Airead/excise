/**
 * @file getaddrinfo.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/11 13:49:14
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUF_SIZE 500

#if 0
struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               size_t           ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };
#endif

static void addrinfo_dump(struct addrinfo *ai)
{
    char addr[INET6_ADDRSTRLEN] = "unknown";
    struct sockaddr_in *sa = NULL;
    struct sockaddr_in6 *sa6 = NULL;

    fprintf(stdout, "=================================\n");
    /*
     * ai_flags
     */
    fprintf(stdout, "ai_flags: ");
    switch (ai->ai_flags) {
    case AF_INET:
        fprintf(stdout, "AF_INET");
        break;
    case AF_INET6:
        fprintf(stdout, "AF_INET6");
        break;
    default:
        fprintf(stdout, "unknown\n");
        break;
    }

    /*
     * ai_family
     */
    fprintf(stdout, "ai_family: %d, ", ai->ai_family);
    switch (ai->ai_family) {
    case AF_INET:
        fprintf(stdout, "AF_INET");
        break;
    case AF_INET6:
        fprintf(stdout, "AF_INET6");
        break;
    default:
        fprintf(stdout, "unknown");
        break;
    }
    fprintf(stdout, "\n");

    /*
     * ai_socktype
     */
    fprintf(stdout, "ai_socktype: %d, ", ai->ai_socktype);
    switch (ai->ai_socktype) {
    case SOCK_STREAM:
        fprintf(stdout, "SOCK_STREAM");
        break;
    case SOCK_DGRAM:
        fprintf(stdout, "SOCK_DGRAM");
        break;
    default:
        fprintf(stdout, "unknown");
        break;
    }
    fprintf(stdout, "\n");

    /*
     * ai_protocol
     */
    fprintf(stdout, "ai_protocol: %d, ", ai->ai_protocol);
    switch (ai->ai_protocol) {
    case IPPROTO_TCP:
        fprintf(stdout, "IPPROTO_TCP");
        break;
    case IPPROTO_UDP:
        fprintf(stdout, "IPPROTO_UDP");
        break;
    default:
        fprintf(stdout, "unknown");
        break;
    }
    fprintf(stdout, "\n");

    /*
     * ai_addrlen
     */
    fprintf(stdout, "ai_addrlen: %d, \n", ai->ai_addrlen);
    
    /*
     * ai_addr
     */
    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
    if (ai->ai_family == AF_INET) {
        sa = (struct sockaddr_in *)ai->ai_addr;
        if (inet_ntop(ai->ai_family, &sa->sin_addr, addr, sizeof(addr)) == NULL) {
            perror("inet_ntop:");
        }
    } else if (ai->ai_family == AF_INET6) {
        sa6 = (struct sockaddr_in6 *)ai->ai_addr;
        if (inet_ntop(ai->ai_family, &sa6->sin6_addr, addr, sizeof(addr)) == NULL) {
            perror("inet_ntop:");
        }
    }
    fprintf(stdout, "ai_addr: %s\n", addr);
 
    /*
     * ai_canonname
     */
    if (ai->ai_canonname != NULL) {
        fprintf(stdout, "ai_canonname: %s\n", ai->ai_canonname);
    }
}

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "getaddrinfo successful\n");

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        addrinfo_dump(rp);
        /* sfd = socket(rp->ai_family, rp->ai_socktype,
         *              rp->ai_protocol);
         * if (sfd == -1)
         *     continue;
         * 
         * if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
         *     break;                  /\* Success *\/
         * 
         * close(sfd); */
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    return 0;
}
