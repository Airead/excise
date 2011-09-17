#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int fd;
  unsigned short port;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
  {
    fprintf(stderr, "Failed to create new UDP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new UDP socket, fd = %d\n", fd);

  //------------------------------------------------------------------
  // step 1.5, bind() is optional
  //------------------------------------------------------------------

  int optval;

  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, &optval, sizeof(optval)) < 0)
  {
    fprintf(stderr, "setsockopt(IP_MULTICAST_LOOP) failed: %s\n", strerror(errno));
  }

  struct in_addr interface_addr;

  inet_pton(AF_INET, argv[4], &interface_addr);
  if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &interface_addr, sizeof(interface_addr)) < 0)
  {
    fprintf(stderr, "setsockopt(IP_MULTICAST_IF) failed: %s\n", strerror(errno));
  }

  //------------------------------------------------------------------
  // step 2, sendto
  //------------------------------------------------------------------
  struct sockaddr_in peer_ipv4_address;

  memset(&peer_ipv4_address, 0, sizeof(peer_ipv4_address));

  peer_ipv4_address.sin_family = AF_INET;	// IPv4
  peer_ipv4_address.sin_port = htons(port);	// network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &peer_ipv4_address.sin_addr);

  ssize_t sent;

  //ssize_t sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
  if ((sent = sendto(fd, argv[3], strlen(argv[3]), 0, (struct sockaddr *) &peer_ipv4_address, sizeof(peer_ipv4_address))) < 0)
  {
    // failed
    fprintf(stderr, "Send %d bytes to %s:%d failed: %s\n", strlen(argv[3]), argv[1], port, strerror(errno));
    // FIXME: How to do?
  }
  else
  {
    // success
    fprintf(stdout, "Send %d bytes to %s:%d successfully.\n", strlen(argv[3]), argv[1], port);
  }

  //------------------------------------------------------------------
  // step 4, close
  //------------------------------------------------------------------
  close(fd);

  return 0;
}
