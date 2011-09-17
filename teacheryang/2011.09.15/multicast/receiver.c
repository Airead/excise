#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void signal_handler(int s);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
// Usage: ./receiver <bind ip> <port port> <multicast group address> <interface>
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
    // failed
    fprintf(stderr, "Failed to create UDP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new UDP socket, fd = %d\n", fd);

  //------------------------------------------------------------------
  // step 2, bind()
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = AF_INET;
  local_ipv4_address.sin_port = htons(port);	//network byte order
  inet_pton(AF_INET, argv[1], &local_ipv4_address.sin_addr);

  // int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(fd, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    fprintf(stderr, "Bind to %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(fd);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%d successfully.\n", argv[1], port);

  //------------------------------------------------------------------
  // step 3, join multicast group
  //------------------------------------------------------------------
  struct ip_mreq mreq;

#if 0
  struct ip_mreq
  {
    struct in_addr imr_multiaddr;	/* IP multicast address of group */
    struct in_addr imr_interface;	/* local IP address of interface */
  };
#endif

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[3], &mreq.imr_multiaddr);
  inet_pton(AF_INET, argv[4], &mreq.imr_interface);

  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
  {
    fprintf(stderr, "Join multicast group failed: %s\n", strerror(errno));
  }
  else
  {
    fprintf(stderr, "Join multicast group successfully.\n");
  }

  //------------------------------------------------------------------
  // Register signal handler
  //------------------------------------------------------------------
  struct sigaction act, oact;

#if 0
  struct sigaction
  {
    void (*sa_handler) (int);
    void (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  }
#endif

  memset(&act, 0, sizeof(act));

  act.sa_handler = signal_handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  //signal(SIGINT, signal_handler);
  //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  sigaction(SIGINT, &act, &oact);
  
  //------------------------------------------------------------------
  // step 4, recvfrom()
  //------------------------------------------------------------------
  char buffer[BUFFER_SIZE];
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";
  ssize_t n;

  for (;;)
  {
    if (global_exit_flag > 0)
    {
      fprintf(stdout, "It's time to exit.\n");
      break;
    }

    peer_ipv4_address_length = sizeof(peer_ipv4_address);

    //again:
    //ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t * fromlen);
    if ((n = recvfrom(fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
    {
      // failed
      if (errno == EINTR)
      {
	//goto again;
	continue;
      }
      else
      {
	fprintf(stderr, "Receive data from multicast group failed: %s\n", strerror(errno));
	// FIXME: How to do?
      }
    }
    else
    {
      // success
      memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));
      inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

      buffer[n] = '\0';
      fprintf(stdout, "Received %d bytes from %s:%d: %s\n", n, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port), buffer);
    }
  }

  // step 5, leave multicast group
  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[3], (void *)&mreq.imr_multiaddr);
  inet_pton(AF_INET, argv[4], (void *)&mreq.imr_interface);

  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  if (setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
  {
    fprintf(stderr, "Leave multicast group failed: %s\n", strerror(errno));
  }
  else
  {
    fprintf(stderr, "Leave multicast group successfully.\n");
  }

  // step 6, close socket
  close(fd);

  return 0;
}

void signal_handler(int s)
{
  fprintf(stdout, "Caught signal %d\n", s);
  global_exit_flag++;
}
