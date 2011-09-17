#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definitions
//--------------------------------------------------------------------
#define LISTEN_BACKLOG	10

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int listening_socket;
  unsigned short port;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Create new TCP socket failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new TCP socket, listening_socket = %d\n", listening_socket);

  //------------------------------------------------------------------
  // step 1.5, Set SO_REUSEADDR & SO_REUSEPORT options
  //------------------------------------------------------------------
  int optval;

  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  
#ifdef SO_REUSEPORT
  optval = 1;
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

  //------------------------------------------------------------------
  // step 2, bind is required
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

#if 0
  struct sockaddr_in
  {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
  };
#endif

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = AF_INET;	// IPv4
  local_ipv4_address.sin_port = htons(port);	// network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &local_ipv4_address.sin_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    fprintf(stderr, "Bind to %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%d.\n", argv[1], port);

  //------------------------------------------------------------------
  // step 3, listen
  //------------------------------------------------------------------
  // int listen(int sockfd, int backlog);
  if (listen(listening_socket, LISTEN_BACKLOG) < 0)
  {
    fprintf(stderr, "Listen on %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listening on %s:%d, wating for incomming connections ...\n", argv[1], port);

  //------------------------------------------------------------------
  // step 4, accept, get a new connected socket, original socket still listen
  //------------------------------------------------------------------
  int new_connected_socket;
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;

  for (;;)
  {
    // peer_ipv4_address_length is value-result parameter, may be changed by accept()
    peer_ipv4_address_length = sizeof(peer_ipv4_address);

  accept_again:
    //int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
    if ((new_connected_socket = accept(listening_socket, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
    {
      // failed
      if (errno == EINTR)
      {
	goto accept_again;
      }
      else
      {
	fprintf(stderr, "Accept incomming connection failed: %s\n", strerror(errno));
	// FIXME: How to do?
	// I prefer to close current listening socket, create a new one
      }
    }
    else
    {
      // success
      char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";

      memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));

      //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
      inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

      fprintf(stdout, "Accepted a new connection %d from %s:%d\n", new_connected_socket, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

      //--------------------------------------------------------------
      // TODO: Add black list or white list to permit/deny incomming connections
      //--------------------------------------------------------------

      //--------------------------------------------------------------
      // step 5, r/w on new connected socket
      //--------------------------------------------------------------
      char banner[] = "Welcome to BSEC TCP test server, version 0.1\n";

      //ssize_t send(int s, const void *buf, size_t len, int flags);
      send(new_connected_socket, banner, strlen(banner), 0);

      // TODO: read data on new_connected_socket

      //--------------------------------------------------------------
      // step 6, close new connected socket
      //--------------------------------------------------------------
      close(new_connected_socket);
    }
  }

  //------------------------------------------------------------------
  // step 8, close listening socket
  //------------------------------------------------------------------
  close(listening_socket);

  return 0;
}
