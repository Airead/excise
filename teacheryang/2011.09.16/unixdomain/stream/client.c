#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	1024

int main(int argc, char **argv)
{
  int fd;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Create new TCP socket failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new TCP socket, fd = %d\n", fd);

  //------------------------------------------------------------------
  // step 2, bind is optional
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  // step 3, connect
  //------------------------------------------------------------------
  struct sockaddr_un remote_unixdomain_address;	// IPv4 address structure

  memset(&remote_unixdomain_address, 0, sizeof(remote_unixdomain_address));

  remote_unixdomain_address.sun_family = AF_UNIX;	// IPv4 address family
  memcpy(remote_unixdomain_address.sun_path, argv[1], strlen(argv[1]));

  //int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
  if (connect(fd, (struct sockaddr *) &remote_unixdomain_address, sizeof(remote_unixdomain_address)) < 0)
  {
    fprintf(stderr, "Connect to remote server %s failed: %s\n", argv[1], strerror(errno));
    close(fd);
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t n;

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
	fprintf(stderr, "Read from remote server failed: %s\n", strerror(errno));
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
