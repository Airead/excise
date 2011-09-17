#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024
#define LISTEN_BACKLOG	10

//--------------------------------------------------------------------
// Type definition
//--------------------------------------------------------------------
typedef struct
{
  void *data;
  unsigned long size;
  unsigned long payload_length;
} buffer_t;

typedef struct
{
  buffer_t *rbuf;		// receive buffer
  buffer_t *sbuf;		// send buffer
} conn_t;

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
struct pollfd global_pollfd[1024];
int global_conn_index = 0;

conn_t **global_conn_list = NULL;
int global_conn_list_num = 0;

volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void do_extra_job(void);

void *utils_safe_malloc(int n);
void utils_safe_free(void *p);

int init_conn_list(int n);
void destroy_conn_list(void);

buffer_t *create_buffer_object(void);
void destroy_buffer_object(buffer_t * buf);

conn_t *create_conn_object(void);
void destroy_conn_object(conn_t * c);

void sigpipe_handler(int sig);
void sigterm_handler(int sig);

void net_accept(int listening_socket);
void net_read(int index, int fd);
void net_write(int index, int fd);

int buffered_send(int fd, const void *data, unsigned long length);

void re_construct_pollfd(void);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int listening_socket;
  unsigned short port;

  init_conn_list(1024);

  port = (unsigned short) strtol(argv[2], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    // failed
    fprintf(stderr, "Cannot create TCP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Create a new TCP socket, listening_socket = %d\n", listening_socket);

  int optval = 1;

  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

#ifdef SO_REUSEPORT
  optval = 1;
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

  //------------------------------------------------------------------
  // step 2, bind
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = AF_INET;
  local_ipv4_address.sin_port = htons(port);

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], (void *) &local_ipv4_address.sin_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    // failed
    fprintf(stderr, "bind() failed: %s\n", strerror(errno));
    close(listening_socket);
    exit(1);
  }

  //------------------------------------------------------------------
  // step 3, listen
  //------------------------------------------------------------------
  // int listen(int sockfd, int backlog);
  if (listen(listening_socket, LISTEN_BACKLOG) < 0)
  {
    // failed
    fprintf(stderr, "listen() failed: %s\n", strerror(errno));
    close(listening_socket);
    exit(1);
  }

  //------------------------------------------------------------------
  // Add listening_socket to global_read_set
  //------------------------------------------------------------------
#if 0
  struct pollfd
  {
    int fd;			/* file descriptor */
    short events;		/* requested events */
    short revents;		/* returned events */
  };
#endif

  global_pollfd[global_conn_index].fd = listening_socket;
  global_pollfd[global_conn_index].events = POLLIN | POLLPRI;

  global_conn_index++;

  signal(SIGPIPE, sigpipe_handler);

  signal(SIGINT, sigterm_handler);
  signal(SIGQUIT, sigterm_handler);
  signal(SIGTERM, sigterm_handler);

  //------------------------------------------------------------------
  // Main loop
  //------------------------------------------------------------------
  for (;;)
  {
    // graceful exit
    if (global_exit_flag > 0)
    {
      // FIXME: cleanup, close all opened sockets
      fprintf(stdout, "It's time to exit.\n");
      break;
    }

    //----------------------------------------------------------------
    // re-construct global_pollfd
    //----------------------------------------------------------------
    re_construct_pollfd();

    //----------------------------------------------------------------
    // Prepare parameters
    //----------------------------------------------------------------
    int n;
    int timeout = 1000;

  poll_again:
    //int poll(struct pollfd *fds, nfds_t nfds, int timeout);
    if ((n = poll(global_pollfd, global_conn_index, timeout)) < 0)
    {
      // error
      if (errno == EINTR)
      {
	goto poll_again;
      }
      else
      {
	fprintf(stderr, "poll() failed: %s\n", strerror(errno));
	// FIXME: How to do?
	break;
      }
    }
    else if (n == 0)
    {
      // timeout
      fprintf(stdout, "timeout ...\n");
      do_extra_job();
    }
    else
    {
      // some file descriptor are ready
      int i;

      for (i = 0; i < global_conn_index; i++)
      {
	if (global_pollfd[i].revents & POLLIN || global_pollfd[i].revents & POLLPRI)
	{
	  // ready to read
	  if (global_pollfd[i].fd == listening_socket)
	  {
	    // accept new incomming connection
	    net_accept(global_pollfd[i].fd);
	  }
	  else
	  {
	    // read data on socket i
	    fprintf(stdout, "%d is ready for reading.\n", i);
	    net_read(i, global_pollfd[i].fd);
	  }
	}

	if (global_pollfd[i].revents & POLLOUT)
	{
	  // ready to write
	  fprintf(stdout, "%d is ready for writing.\n", i);
	  net_write(i, global_pollfd[i].fd);
	}

#if 0
	if (global_pollfd[i].revents & POLLOUT)
	{
	  // exception
	  fprintf(stdout, "%d is exception.\n", i);
	}
#endif
      }
    }
  }

  destroy_conn_list();

  return 0;
}

void do_extra_job(void)
{
  fprintf(stdout, "Do extra job ...\n");
}

void *utils_safe_malloc(int n)
{
  void *p = malloc(n);

  if (p == NULL)
  {
    fprintf(stderr, "Allocate memory failed, required size = %d\n", n);
    return NULL;
  }
  else
  {
    return p;
  }
}

void utils_safe_free(void *p)
{
  if (p)
  {
    free(p);
    p = NULL;			// useless
  }
}

int init_conn_list(int n)
{
  global_conn_list = utils_safe_malloc(n * sizeof(conn_t *));

  if (global_conn_list == NULL)
  {
    return -1;
  }

  global_conn_list_num = n;

  int i;

  for (i = 0; i < n; i++)
  {
    global_conn_list[i] = NULL;
  }

  return 0;
}

void destroy_conn_list(void)
{
  int i;

  for (i = 0; i < global_conn_list_num; i++)
  {
    if (global_conn_list[i])
    {
      //utils_safe_free(global_conn_list[i]);
      destroy_conn_object(global_conn_list[i]);
    }
  }

  utils_safe_free(global_conn_list);
  global_conn_list = NULL;
}

conn_t *create_conn_object(void)
{
  conn_t *c = utils_safe_malloc(sizeof(conn_t));

  if (!c)
  {
    return NULL;
  }

  c->rbuf = create_buffer_object();
  c->sbuf = create_buffer_object();

  if (!c->rbuf || !c->sbuf)
  {
    utils_safe_free(c->rbuf);
    utils_safe_free(c->sbuf);
    utils_safe_free(c);
    return NULL;
  }

  return c;
}

void destroy_conn_object(conn_t * c)
{
  if (c)
  {
    destroy_buffer_object(c->rbuf);
    destroy_buffer_object(c->sbuf);
  }

  utils_safe_free(c);
  c = NULL;
}

buffer_t *create_buffer_object(void)
{
  buffer_t *buf = utils_safe_malloc(sizeof(buffer_t));

  if (buf == NULL)
  {
    return NULL;
  }

  buf->data = utils_safe_malloc(BUFFER_SIZE);

  if (!buf->data)
  {
    utils_safe_free(buf);
    return NULL;
  }

  buf->size = BUFFER_SIZE;
  buf->payload_length = 0;

  return buf;
}

void destroy_buffer_object(buffer_t * buf)
{
  if (buf)
  {
    utils_safe_free(buf->data);
    utils_safe_free(buf);
    buf = NULL;
  }
}

void net_accept(int listening_socket)
{
  int new_accepted_socket;
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";

  peer_ipv4_address_length = sizeof(peer_ipv4_address);

  //int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
  if ((new_accepted_socket = accept(listening_socket, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
  {
    // accept failed
    fprintf(stderr, "accept() failed: %s\n", strerror(errno));
    // FIXME: How to do?
  }
  else
  {
    memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));

    inet_ntop(AF_INET, (void *) &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

    // Accepted a new connection
    fprintf(stdout, "Accepted a new connection %d from %s:%d.\n", new_accepted_socket, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

    // create new conn object
    conn_t *c = create_conn_object();

    if (!c)
    {
      fprintf(stderr, "Create conn object failed, close new accepted socket, i'm sorry.\n");

      close(new_accepted_socket);
    }
    else
    {
      if (global_conn_list[new_accepted_socket])
      {
	fprintf(stderr, "Fatal error: conn object exists.\n");
	close(new_accepted_socket);
	destroy_conn_object(c);
	c = NULL;
      }
      else
      {
	// attach to connection list
	global_conn_list[new_accepted_socket] = c;

	global_pollfd[global_conn_index].fd = new_accepted_socket;
	global_pollfd[global_conn_index].events = POLLIN | POLLPRI;

	global_conn_index++;
      }
    }
  }
}

void net_read(int index, int fd)
{
  conn_t *current;

  current = global_conn_list[fd];

  if (!current)
  {
    // error
    // FIXME: error handle
  }

  ssize_t received_bytes;

  //ssize_t read(int fd, void *buf, size_t count);
  if ((received_bytes = read(fd, current->rbuf->data + current->rbuf->payload_length, current->rbuf->size - current->rbuf->payload_length)) < 0)
  {
    // error
    fprintf(stderr, "read() failed on socket %d: %s\n", fd, strerror(errno));
    // FIXME: How to do?
  }
  else if (received_bytes == 0)
  {
    // connection closed by peer.
    fprintf(stdout, "Connection %d closed by peer.\n", fd);
    close(fd);

    destroy_conn_object(current);
    global_conn_list[fd] = NULL;

    global_pollfd[index].fd = -1;
    global_pollfd[index].events = 0;
  }
  else
  {
    // success
    fprintf(stdout, "Read %d bytes on connection %d.\n", received_bytes, fd);

    current->rbuf->payload_length += received_bytes;

    if (current->rbuf->payload_length >= current->rbuf->size)
    {
      int newsize = current->rbuf->size * 2;
      void *newdata = utils_safe_malloc(newsize);

      // allocate more resource for rbuf
      if (newdata)
      {
	//void *memcpy(void *dest, const void *src, size_t n);
	memcpy(newdata, current->rbuf->data, current->rbuf->payload_length);
	utils_safe_free(current->rbuf->data);
	current->rbuf->data = newdata;
	current->rbuf->size = newsize;
      }
      else
      {
	// failed
	// FIXME: How to do?
      }
    }
  }
}

void net_write(int index, int fd)
{
  conn_t *current;
  ssize_t written;

  current = global_conn_list[fd];

  if (!current)
  {
    // FIXME: error handle
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  if ((written = write(fd, current->sbuf->data, current->sbuf->payload_length)) < 0)
  {
    // error
    if (errno == EPIPE)
    {
      // Connection close by peer.
      fprintf(stdout, "Connection %d closed by peer.\n", fd);
      close(fd);

      destroy_conn_object(current);
      global_conn_list[fd] = NULL;

      global_pollfd[index].fd = -1;
      global_pollfd[index].events = 0;
    }
    else
    {

      fprintf(stderr, "write() failed on connetion %d: %s.\n", fd, strerror(errno));
      // FIXME: How to do?
    }
  }
  else
  {
    //void *memmove(void *dest, const void *src, size_t n);
    memmove(current->sbuf->data, current->sbuf->data + written, current->sbuf->payload_length - written);

    current->sbuf->payload_length -= written;

    if (current->sbuf->payload_length == 0)
    {
      global_pollfd[index].events &= ~POLLOUT;
    }
  }
}

int buffered_send(int fd, const void *data, unsigned long length)
{
  conn_t *c;

  c = global_conn_list[fd];

  if (!c)
  {
    fprintf(stderr, "Bad target!\n");
    return -1;
  }

  if (c->sbuf->size - c->sbuf->payload_length < length)
  {
    int newsize = c->sbuf->payload_length + length;
    void *newdata = utils_safe_malloc(newsize);

    if (newdata)
    {
      memcpy(newdata, c->sbuf->data, c->sbuf->payload_length);
      memcpy(newdata + c->sbuf->payload_length, data, length);

      utils_safe_free(c->sbuf->data);

      c->sbuf->data = newdata;
      c->sbuf->payload_length += length;
    }
    else
    {
      fprintf(stderr, "Cannot allocate memory for newdata, requriured = %d.\n", newsize);
      // FIXME: How to do?
      return -1;
    }
  }

  if (c->sbuf->payload_length > 0)
  {
    int i;

    for (i = 0; i < global_conn_index; i++)
    {
      if (global_pollfd[i].fd == fd)
      {
	// found
	global_pollfd[i].events |= POLLOUT;
	break;
      }
    }
  }

  return 0;
}

void sigpipe_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
}

void sigterm_handler(int sig)
{
  fprintf(stdout, "Caught signal %d.\n", sig);
  global_exit_flag++;
}

void re_construct_pollfd(void)
{
  int i;
  int new_index = 0;

  while (i < global_conn_index)
  {
    if (global_pollfd[i].fd == -1)
    {
      i++;
      continue;
    }

    global_pollfd[new_index] = global_pollfd[i];

    new_index++;
    i++;
  }

  global_conn_index = new_index;
}
