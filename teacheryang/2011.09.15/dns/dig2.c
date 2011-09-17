#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

char *sock_type_string[] = {
  "",
  "SOCK_STREAM",		//SOCK_STREAM = 1
  "SOCK_DGRAM",			//SOCK_DGRAM = 2
  "SOCK_RAW",			//SOCK_RAW = 3
  "SOCK_RDM",			//SOCK_RDM = 4
  "SOCK_SEQPACKET",		//SOCK_SEQPACKET = 5
  "",
  "",
  "",
  "",
  "SOCK_PACKET"			//SOCK_PACKET = 10
};

int main(int argc, char **argv)
{
  int result;
  struct addrinfo *res;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));

#if 0
#  define AI_PASSIVE	0x0001	/* Socket address is intended for `bind'.  */
#  define AI_CANONNAME	0x0002	/* Request for canonical name.  */
#  define AI_NUMERICHOST	0x0004	/* Don't use name resolution.  */
#  define AI_V4MAPPED	0x0008	/* IPv4 mapped addresses are acceptable.  */
#  define AI_ALL		0x0010	/* Return IPv4 mapped and IPv6 addresses.  */
#  define AI_ADDRCONFIG	0x0020	/* Use configuration of this host to choose */
#endif

  hints.ai_flags = AI_PASSIVE | AI_CANONNAME | AI_V4MAPPED | AI_ALL | AI_ADDRCONFIG;
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;

  //int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
  if ((result = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
  {
    // getaddrinfo(3) returns 0 if it succeeds
    // The  gai_strerror(3) function translates these error codes to a human readable string, suitable for error reporting
    //const char *gai_strerror(int errcode);
    fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(result));
    exit(1);
  }

#if 0
  struct addrinfo
  {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;
    struct sockaddr *ai_addr;
    char *ai_canonname;
    struct addrinfo *ai_next;
  };
#endif

  while (res)
  {
#if 0
    fprintf(stdout, "ai_flags = 0x%08x\n", res->ai_flags);
    fprintf(stdout, "ai_family = %d(%s)\n", res->ai_family, res->ai_family == AF_INET ? "IPv4" : "IPv6");
    fprintf(stdout, "ai_socktype = %d(%s)\n", res->ai_socktype, sock_type_string[res->ai_socktype]);
    fprintf(stdout, "ai_protocol = %d\n", res->ai_protocol);
    fprintf(stdout, "ai_addrlen = %d\n", res->ai_addrlen);
    fprintf(stdout, "ai_canonname: %s\n", res->ai_canonname);
#endif

    struct protoent *p;

#if 0
    struct protoent
    {
      char *p_name;		/* official protocol name */
      char **p_aliases;		/* alias list */
      int p_proto;		/* protocol number */
    };
#endif

    //struct protoent *getprotobynumber(int proto);
    p = getprotobynumber(res->ai_protocol);

    fprintf(stdout, "0x%08x  %-4s(%02d)  %-12s(%02d)  %-4s(%02d)  %02d  %-16s  ", res->ai_flags, res->ai_family == AF_INET ? "IPv4" : "IPv6", res->ai_family, sock_type_string[res->ai_socktype], res->ai_socktype, p->p_name, res->ai_protocol, res->ai_addrlen, res->ai_canonname);

    if (res->ai_addr->sa_family == AF_INET)
    {
      // IPv4
      char ipv4_string[32];
      struct sockaddr_in *ipv4_address = (struct sockaddr_in *) (res->ai_addr);

      memset(ipv4_string, 0, sizeof(ipv4_string));
      //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
      inet_ntop(res->ai_addr->sa_family, &ipv4_address->sin_addr, ipv4_string, sizeof(ipv4_string));
      fprintf(stdout, "IP: %s\n", ipv4_string);
    }
    else if (res->ai_addr->sa_family == AF_INET6)
    {
      // IPv6
      char ipv6_string[128];
      struct sockaddr_in6 *ipv6_address = (struct sockaddr_in6 *) (res->ai_addr);

      memset(ipv6_string, 0, sizeof(ipv6_string));
      //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
      inet_ntop(res->ai_addr->sa_family, &ipv6_address->sin6_addr, ipv6_string, sizeof(ipv6_string));
      fprintf(stdout, "IP: %s\n", ipv6_string);
    }
    else
    {
      // Do nothing.
    }

    res = res->ai_next;
  }

  //void freeaddrinfo(struct addrinfo *res);
  freeaddrinfo(res);

  return 0;
}
