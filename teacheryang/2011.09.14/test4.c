#include <stdio.h>
#include <arpa/inet.h>		// ipv4, ipv6
#include <sys/un.h>		// unixdomain

int main(int argc, char **argv)
{
  int fd;
  unsigned short port_number;

  //------------------------------------------------------------------
  // Generic usage address structure
  //------------------------------------------------------------------
  struct sockaddr generic_address;

#if 0
  struct sockaddr
  {
    sa_family_t sa_family;
    char sa_data[14];
  };
#endif

  //------------------------------------------------------------------
  // IPv4 address structure
  //------------------------------------------------------------------
  struct sockaddr_in ipv4_address;

#if 0
  struct sockaddr_in
  {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
  };
#endif

  // step 1, clear
  memset(&ipv4_address, 0, sizeof(ipv4_address));

  // step 2, assign number to every fields
  ipv4_address.sin_family = AF_INET;	// IPv4
  ipv4_address.sin_port = htons(port_number);	// network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, "192.168.1.101", (void *) &ipv4_address.sin_addr);

  // step 3, call bind(), connect(), accept(), sendto(), recvfrom() with argument
  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  bind(fd, (struct sockaddr *) &ipv4_address, sizeof(ipv4_address));

  //int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  connect(fd, (struct sockaddr *) &ipv4_address, sizeof(ipv4_address));

  //------------------------------------------------------------------
  // IPv6 address structure
  //------------------------------------------------------------------
  struct sockaddr_in6 ipv6_address;

#if 0
  struct sockaddr_in6
  {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
  };
#endif

  memset(&ipv6_address, 0, sizeof(ipv6_address));

  ipv6_address.sin6_family = AF_INET6;	// IPv6
  ipv6_address.sin6_port = htons(port_number);	// network byte order
  //TODO: ipv6_address.sin6_flowinfo = 

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET6, "fe80::20d:60ff:fecb:86e5", &ipv6_address.sin6_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  bind(fd, (struct sockaddr *) &ipv6_address, sizeof(ipv6_address));

  //int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  connect(fd, (struct sockaddr *) &ipv6_address, sizeof(ipv6_address));

  //------------------------------------------------------------------
  // unixdomain address structure
  //------------------------------------------------------------------
  struct sockaddr_un unixdomain_address;

#if 0
  struct sockaddr_un
  {
    sa_family_t sun_family;
    char sun_path[108];
  };
#endif

  memset(&unixdomain_address, 0, sizeof(unixdomain_address));

  unixdomain_address.sun_family = AF_UNIX;	//AF_LOCAL, Unix domain

#define UNIXDOMAIN_SOCKET	"/tmp/abc.sock"	// just a filename

  // BAD MANNER: char *strcpy(char *dest, const char *src);
  // char *strncpy(char *dest, const char *src, size_t n);

  //void *memcpy(void *dest, const void *src, size_t n);
  memcpy(unixdomain_address.sun_path, UNIXDOMAIN_SOCKET, strlen(UNIXDOMAIN_SOCKET));

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  bind(fd, (struct sockaddr *) &unixdomain_address, sizeof(unixdomain_address));

  //int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  connect(fd, (struct sockaddr *) &unixdomain_address, sizeof(unixdomain_address));

#if 0
  int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
  ssize_t sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
  ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t * fromlen);
#endif

  return 0;
}
