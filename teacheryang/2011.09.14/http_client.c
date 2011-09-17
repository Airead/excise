#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

int main(int argc, char **argv)
{
  int fd;

  unsigned short port;

  //long int strtol(const char *nptr, char **endptr, int base);
  port = (unsigned short) strtol(argv[2], NULL, 10);

  // step 1, create socket
  //int socket(int domain, int type, int protocol);
  if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Create new TCP socket failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new TCP socket, fd = %d\n", fd);

  // step 2, bind is optional

  // step 3, connect
  struct sockaddr_in remote_ipv4_address;	// IPv4 address structure

#if 0
  struct sockaddr_in
  {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
  };
#endif

  memset(&remote_ipv4_address, 0, sizeof(remote_ipv4_address));

  remote_ipv4_address.sin_family = AF_INET;	// IPv4 address family
  remote_ipv4_address.sin_port = htons(port);	// network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &remote_ipv4_address.sin_addr);

  //int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  if (connect(fd, (struct sockaddr *) &remote_ipv4_address, sizeof(remote_ipv4_address)) < 0)
  {
    fprintf(stderr, "Connect to remote server %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(fd);
    exit(1);
  }

  // http://www.w3.org/Protocols/rfc2616/rfc2616.html
  char http_request[] = "GET /\n\n";

  //ssize_t write(int fd, const void *buf, size_t count);
  ssize_t n;
  int required = strlen(http_request);
  int total = 0;

  while (total < required)
  {
  again:
    if ((n = write(fd, http_request + total, required - total)) < 0)
    {
      // error
      if (errno == EINTR)
      {
	goto again;
      }
      else
      {
	fprintf(stderr, "Send request to remote server failed: %s\n", strerror(errno));
	break;
      }
    }
    else
    {
      total += n;
    }
  }

  char buffer[BUFFER_SIZE];

  for (;;)
  {
    // step 4, r/w on connected socket
  read_again:
    //ssize_t read(int fd, void *buf, size_t count);
    if ((n = read(fd, buffer, sizeof(buffer) - 1)) < 0)
    {
      // error
      if (errno == EINTR)
      {
	goto read_again;
      }
      else
      {
	fprintf(stderr, "Read response failed: %s\n", strerror(errno));
	break;
      }
    }
    else if (n == 0)
    {
      // connection closed by peer.
      close(fd);
      break;
    }
    else
    {
      buffer[n] = '\0';
      fprintf(stdout, "Recevied %d bytes from remote server: %s\n", n, buffer);
    }
  }

  // step 5, close
  close(fd);

  return 0;
}
