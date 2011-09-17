#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define MAX_EVENTS 	16
#define LISTENQ		5
#define BUFFER_SIZE	1024

int main(int argc, char **argv)
{
  int listening_socket;

  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Cannot create new TCP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Create a new TCP socket %d.\n", listening_socket);

  int value;

  value = 1;

  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

#ifdef SO_REUSEPORT
  value = 1;
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
#endif

  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = PF_INET;
  local_ipv4_address.sin_addr.s_addr = inet_addr(argv[1]);
  local_ipv4_address.sin_port = htons(atoi(argv[2]));

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    fprintf(stderr, "bind() failed: %s\n", strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%s\n", argv[1], argv[2]);

  //int listen(int sockfd, int backlog);
  if (listen(listening_socket, LISTENQ) < 0)
  {
    fprintf(stderr, "listen() failed: %s\n", strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listening ...\n");

  int epfd;

  /* Open  an epoll file descriptor by requesting the kernel allocate an event 
   * backing store dimensioned for size descriptors. The size is not the maximum
   * size of the backing store but just a hint to the kernel about how to 
   * dimension internal  structures. The returned file descriptor will be used 
   * for all the subsequent calls to the epoll interface. The file descriptor  
   * returned  by  epoll_create(2) must be closed by using close(2).
   */

  /* When  successful,  epoll_create(2)  returns  a non-negative integer identifying 
   * the descriptor.  When an error occurs,  epoll_create(2) returns -1 and errno 
   * is set appropriately.
   */
  //int epoll_create(int size);
  if ((epfd = epoll_create(1024)) < 0)
  {
    fprintf(stderr, "epoll_create() failed: %s\n", strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "epoll_create() successfully, epfd = %d\n", epfd);

  struct epoll_event event;

  memset(&event, 0, sizeof(event));

  /*
   * EPOLLIN
   * 
   * The associated file is available for read(2) operations.
   *
   * EPOLLOUT
   *
   * The associated file is available for write(2) operations.
   *
   * EPOLLRDHUP
   * 
   * Stream  socket  peer  closed  connection,  or shut down writing half of connection.  (This flag is
   * especially useful for writing simple code to detect peer shutdown when using Edge Triggered  moni-
   * toring.)
   *
   * EPOLLPRI
   *
   * There is urgent data available for read(2) operations.
   *    
   * EPOLLERR
   *
   * Error  condition  happened  on the associated file descriptor.  epoll_wait(2) will always wait for
   * this event; it is not necessary to set it in events.
   *
   * EPOLLHUP
   *
   * Hang up happened on the associated file descriptor.   epoll_wait(2)  will  always  wait  for  this
   * event; it is not necessary to set it in events.
   *
   * EPOLLET
   * 
   * Sets  the  Edge Triggered behaviour for the associated file descriptor.  The default behaviour for
   * epoll is Level Triggered. See epoll(7) for more detailed information about Edge  and  Level  Trig-
   * gered event distribution architectures.
   *
   * EPOLLONESHOT (since kernel 2.6.2)
   *
   * Sets the one-shot behaviour for the associated file descriptor.  This means that after an event is
   * pulled out with epoll_wait(2) the associated file descriptor is internally disabled and  no  other
   * events will be reported by the epoll interface. The user must call epoll_ctl(2) with EPOLL_CTL_MOD
   * to re-enable the file descriptor with a new event mask.
   */

  event.data.fd = listening_socket;
  event.events = EPOLLIN | EPOLLOUT;

  //int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, listening_socket, &event) < 0)
  {
    fprintf(stderr, "epoll_ctl() failed: %s\n", strerror(errno));
    close(epfd);
    close(listening_socket);
    exit(1);
  }

  int n;
  struct epoll_event events[MAX_EVENTS];

  for (;;)
  {
    //int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
    if ((n = epoll_wait(epfd, events, MAX_EVENTS, 1000)) < 0)
    {
      fprintf(stderr, "epoll_wait() failed: %s\n", strerror(errno));
      // FIXME: How to do?
    }
    else if (n == 0)
    {
      fprintf(stdout, "Timeout ...\n");
    }
    else
    {
      int i;

      for (i = 0; i < n; i++)
      {
	if (events[i].data.fd == listening_socket)
	{
	  fprintf(stdout, "Ready to accept new incoming connection.\n");

	  int new_accepted_socket;
	  struct sockaddr_in peer_ipv4_address;
	  socklen_t peer_ipv4_address_length;

	  peer_ipv4_address_length = sizeof(peer_ipv4_address);

	  //int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
	  if ((new_accepted_socket = accept(events[i].data.fd, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
	  {
	    fprintf(stderr, "accept() failed: %s\n", strerror(errno));
	    // FIXME: How to do?
	  }
	  else
	  {
	    fprintf(stdout, "Accepted a new connection %d from %s:%d.\n", new_accepted_socket, inet_ntoa(peer_ipv4_address.sin_addr), ntohs(peer_ipv4_address.sin_port));

	    event.data.fd = new_accepted_socket;
	    event.events = EPOLLIN;

	    //int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
	    if (epoll_ctl(epfd, EPOLL_CTL_ADD, new_accepted_socket, &event) < 0)
	    {
	      fprintf(stderr, "epoll_ctl() failed: %s\n", strerror(errno));
	      close(new_accepted_socket);
	    }
	    else
	    {
	      fprintf(stdout, "Add socket #%d to epoll watched descriptors.\n", new_accepted_socket);
	    }
	  }
	}
	else
	{
	  if (events[i].events & EPOLLIN)
	  {
	    fprintf(stdout, "Socket #%d is ready for reading.\n", events[i].data.fd);

	    char buffer[BUFFER_SIZE];
	    ssize_t read_bytes;

	    //ssize_t read(int fd, void *buf, size_t count);
	    if ((read_bytes = read(events[i].data.fd, buffer, sizeof(buffer) - 1)) < 0)
	    {
	      fprintf(stderr, "read() failed on socket #%d: %s\n", events[i].data.fd, strerror(errno));
	      // FIXME: How to do?
	    }
	    else if (read_bytes == 0)
	    {
	      // Connection closed by peer.
	      fprintf(stdout, "On socket #%d, connection closed by peer.\n", events[i].data.fd);
	      close(events[i].data.fd);

	      // fd will be removed from epfd set by epoll automatically
	    }
	    else
	    {
	      buffer[read_bytes] = '\0';
	      fprintf(stdout, "Read %d bytes on socket #%d: %s\n", read_bytes, events[i].data.fd, buffer);
	    }
	  }

	  if (events[i].events & EPOLLOUT)
	  {
	    fprintf(stdout, "Socket #%d is ready for writting.\n", events[i].data.fd);
	  }
	}
      }
    }
  }

  close(listening_socket);

  return 0;
}
