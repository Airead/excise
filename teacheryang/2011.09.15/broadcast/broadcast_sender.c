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

  //------------------------------------------------------------------
  // step 1.6, set SO_BROADCAST option
  //------------------------------------------------------------------
  int optval;

  optval = 1;

  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));

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
  // step 3, recvfrom
  //------------------------------------------------------------------
  char buffer[BUFFER_SIZE];
  socklen_t peer_ipv4_address_length;	// value-result parameter
  char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";
  ssize_t received;

  peer_ipv4_address_length = sizeof(peer_ipv4_address);

  //ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t * fromlen);
  if ((received = recvfrom(fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
  {
    // failed
    fprintf(stderr, "Receive data on socket %d failed: %s\n", fd, strerror(errno));
    // FIXME: How to do?
  }
  else
  {
    // success
    buffer[received] = '\0';

    memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));

    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
    inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

    fprintf(stdout, "Received %d bytes from %s:%d: %s\n", received, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port), buffer);
  }

  //------------------------------------------------------------------
  // step 4, close
  //------------------------------------------------------------------
  close(fd);

  return 0;
}
