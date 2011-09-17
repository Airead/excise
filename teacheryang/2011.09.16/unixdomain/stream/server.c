#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>

// Usage: ./server <socket filename> <backlog>
int main(int argc, char **argv)
{
  int listening_socket;
  int backlog;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  backlog = (int) strtol(argv[2], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Failed to create UNIX domain socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new unixdomain socket, listening_socket = %d\n", listening_socket);

  //------------------------------------------------------------------
  // step 2, bind
  //------------------------------------------------------------------
  struct sockaddr_un local_unixdomain_address;	// UNIX DOMAIN

#if 0
  struct sockaddr_un
  {
    sa_family_t sun_family;
    char sun_path[108];
  }
#endif

  memset(&local_unixdomain_address, 0, sizeof(local_unixdomain_address));

  local_unixdomain_address.sun_family = AF_UNIX;	//AF_LOCAL
  //void *memcpy(void *dest, const void *src, size_t n);
  memcpy(local_unixdomain_address.sun_path, argv[1], strlen(argv[1]));

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_unixdomain_address, sizeof(local_unixdomain_address)) < 0)
  {
    fprintf(stderr, "Bind to %s failed: %s\n", argv[1], strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s successfully.\n", argv[1]);

  //------------------------------------------------------------------
  // step 3, listen
  //------------------------------------------------------------------
  // int listen(int sockfd, int backlog);
  if (listen(listening_socket, backlog) < 0)
  {
    fprintf(stderr, "Listen on %s failed: %s\n", argv[1], strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listening, waiting for incoming connections ...\n");

  //------------------------------------------------------------------
  // step 4, accept
  //------------------------------------------------------------------
  int new_connected_socket;
  struct sockaddr_un peer_unixdomain_address;
  socklen_t peer_unixdomain_address_length;

  for (;;)
  {
    // peer_unixdomain_address_length is value-result parameter, will be modified by accept() calling
    peer_unixdomain_address_length = sizeof(peer_unixdomain_address);

    //int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
    if ((new_connected_socket = accept(listening_socket, (struct sockaddr *) &peer_unixdomain_address, &peer_unixdomain_address_length)) < 0)
    {
      // failed
      fprintf(stderr, "accept() failed: %s\n", strerror(errno));
      // FIXME: How to do?
      break;
    }
    else
    {
      // success
      fprintf(stdout, "Accepted a new connection %d from %s\n", new_connected_socket, peer_unixdomain_address.sun_path);
    }

    //----------------------------------------------------------------
    // step 5, r/w on new_connected_socket
    //----------------------------------------------------------------
    char banner[] = "Welcome to BSEC unixdomain domain test server, ver 0.1\n";

    //ssize_t write(int fd, const void *buf, size_t count);
    write(new_connected_socket, banner, strlen(banner));

    //----------------------------------------------------------------
    // step 6, close new_connected_socket
    //----------------------------------------------------------------
    close(new_connected_socket);
  }

  //------------------------------------------------------------------
  // step 7, close listening_socket
  //------------------------------------------------------------------
  close(listening_socket);

  return 0;
}
