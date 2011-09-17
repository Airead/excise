#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro defintion
//--------------------------------------------------------------------
#define BUFFER_SIZE	1024

//--------------------------------------------------------------------
// Type definition
//--------------------------------------------------------------------
typedef struct
{
  char *data;
  uint32_t size;
  uint32_t payload_length;
} buf_t;

typedef struct
{
  buf_t *rbuf;
  buf_t *sbuf;
} conn_t;

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
fd_set global_read_set, global_write_set, global_except_set;
int global_max_fd = 0;

conn_t **global_conn_list = NULL;
int global_conn_list_num = 0;

volatile sig_atomic_t global_exit_flag = 0;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void net_init(void);
void net_register_read(int fd);
void net_unregister_read(int fd);
void net_register_write(int fd);
void net_unregister_write(int fd);
void net_register_except(int fd);
void net_unregister_except(int fd);

void net_accept(int listening_socket);
int net_read(int fd);
int net_write(int fd);
void net_close_all(void);

void do_extra_job(void);

void *utils_safe_malloc(uint32_t n);
void utils_safe_free(void *p);

int init_conn_list(int n);
void destroy_conn_list(void);

conn_t *create_conn_object(void);
void destroy_conn_object(conn_t * c);

buf_t *create_buf_object(void);
void destroy_buf_object(buf_t * b);

void sigpipe_handler(int sig);
void sigterm_handler(int sig);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int listening_socket;
  unsigned short port;
  int backlog;

  //------------------------------------------------------------------
  // Initialize global_conn_list
  //------------------------------------------------------------------
  init_conn_list(1024);

  //------------------------------------------------------------------
  // Initialize global_read_set, global_write_set, global_except_set
  // Initialize global_max_fd
  //------------------------------------------------------------------
  net_init();

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);
  backlog = (int) strtol(argv[3], NULL, 10);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((listening_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "Failed to create new TCP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new TCP socket, listening_socket = %d\n", listening_socket);

  //------------------------------------------------------------------
  // Set SO_REUSEADDR & SO_REUSEPORT options
  //------------------------------------------------------------------
  int optval;

  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

#ifdef SO_REUSEPORT
  optval = 1;
  //int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

  //------------------------------------------------------------------
  // step 2, bind
  //------------------------------------------------------------------
  struct sockaddr_in local_ipv4_address;

  memset(&local_ipv4_address, 0, sizeof(local_ipv4_address));

  local_ipv4_address.sin_family = AF_INET;
  local_ipv4_address.sin_port = htons(port);	// network byte order

  //int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &local_ipv4_address.sin_addr);

  //int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
  if (bind(listening_socket, (struct sockaddr *) &local_ipv4_address, sizeof(local_ipv4_address)) < 0)
  {
    // failed
    fprintf(stderr, "Bind to %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Bound to %s:%d successfully.\n", argv[1], port);

  //------------------------------------------------------------------
  // step 3, listen
  //------------------------------------------------------------------
  //int listen(int sockfd, int backlog);
  if (listen(listening_socket, backlog) < 0)
  {
    // failed
    fprintf(stderr, "Listen on %s:%d failed: %s\n", argv[1], port, strerror(errno));
    close(listening_socket);
    exit(1);
  }

  fprintf(stdout, "Listen on %s:%d successfully.\n", argv[1], port);

  int n;
  fd_set rset, wset, eset;
  struct timeval to;

  //------------------------------------------------------------------
  // Add listening_socket to global_read_set
  //------------------------------------------------------------------
  net_register_read(listening_socket);

  //------------------------------------------------------------------
  // Register signal handler
  //------------------------------------------------------------------
  signal(SIGPIPE, sigpipe_handler);

  signal(SIGINT, sigterm_handler);
  signal(SIGTERM, sigterm_handler);
  signal(SIGKILL, sigterm_handler);

  //------------------------------------------------------------------
  // Main loop
  //------------------------------------------------------------------
  for (;;)
  {
    if (global_exit_flag > 0)
    {
      // It's time to exit.
      fprintf(stdout, "It's time to exit.\n");
      break;
    }

    rset = global_read_set;
    wset = global_write_set;
    eset = global_except_set;

    to.tv_sec = 1;
    to.tv_usec = 0;

    //int select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout);
    if ((n = select(global_max_fd + 1, &rset, &wset, &eset, &to)) < 0)
    {
      // failed
      if (errno == EINTR)
      {
	continue;
      }
      else
      {
	fprintf(stderr, "select() failed: %s\n", strerror(errno));
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
      // ready
      int i;

      for (i = 0; i <= global_max_fd; i++)
      {
	//int FD_ISSET(int fd, fd_set * set);
	if (FD_ISSET(i, &rset))
	{
	  //----------------------------------------------------------
	  // ready to read
	  //----------------------------------------------------------
	  if (i == listening_socket)
	  {
	    net_accept(i);
	  }
	  else
	  {
	    // i is connected socket, read data
	    fprintf(stdout, "socket %d is ready to read.\n", i);

	    net_read(i);
	  }
	}

	//int FD_ISSET(int fd, fd_set * set);
	if (FD_ISSET(i, &wset))
	{
	  // ready to write
	  fprintf(stdout, "socket %d is ready to write.\n", i);
	  net_write(i);
	}

#if 0
	//int FD_ISSET(int fd, fd_set * set);
	if (FD_ISSET(i, &eset))
	{
	  // exception
	}
#endif
      }
    }
  }

  //------------------------------------------------------------------
  // FIXME: Send rest data in send buffer to clients
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  // Close all sockets
  //------------------------------------------------------------------
  net_close_all();

  //------------------------------------------------------------------
  // Destroy global_conn_list
  //------------------------------------------------------------------
  destroy_conn_list();

  //------------------------------------------------------------------
  // Close listening_socket
  //------------------------------------------------------------------
  close(listening_socket);

  return 0;
}

void net_init(void)
{
  FD_ZERO(&global_read_set);
  FD_ZERO(&global_write_set);
  FD_ZERO(&global_except_set);

  global_max_fd = 0;
}

void net_register_read(int fd)
{
  FD_SET(fd, &global_read_set);

  if (fd > global_max_fd)
  {
    global_max_fd = fd;
  }
}

void net_unregister_read(int fd)
{
  FD_CLR(fd, &global_read_set);
}

void net_register_write(int fd)
{
  FD_SET(fd, &global_write_set);

  if (fd > global_max_fd)
  {
    global_max_fd = fd;
  }
}

void net_unregister_write(int fd)
{
  FD_CLR(fd, &global_write_set);
}

void net_register_except(int fd)
{
  FD_SET(fd, &global_except_set);

  if (fd > global_max_fd)
  {
    global_max_fd = fd;
  }
}

void net_unregister_except(int fd)
{
  FD_CLR(fd, &global_except_set);
}

void do_extra_job(void)
{
  fprintf(stdout, "Do extra job ...\n");
}

int init_conn_list(int n)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s()\n", __func__);
#endif
  uint32_t total = n * sizeof(conn_t *);

  global_conn_list = utils_safe_malloc(total);

  if (global_conn_list == NULL)
  {
    return -1;
  }

  int i;

  for (i = 0; i < n; i++)
  {
    global_conn_list[i] = NULL;
  }

  global_conn_list_num = n;

  return 0;
}

conn_t *create_conn_object(void)
{
  conn_t *c;

  c = utils_safe_malloc(sizeof(conn_t));

  if (!c)
  {
    return NULL;
  }

  c->rbuf = create_buf_object();
  c->sbuf = create_buf_object();

  if (!c->rbuf || !c->sbuf)
  {
    destroy_buf_object(c->rbuf);
    destroy_buf_object(c->sbuf);

    utils_safe_free(c);

    return NULL;
  }

  return c;
}

void destroy_conn_object(conn_t * c)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s()\n", __func__);
#endif

  if (c)
  {
    // free rbuf
    destroy_buf_object(c->rbuf);

    // free sbuf
    destroy_buf_object(c->sbuf);

    // free c
#ifdef _DEBUG_TRACE_
    fprintf(stdout, "attempt to free conn_t object %p\n", c);
#endif
    utils_safe_free(c);

    c = NULL;
  }
}

buf_t *create_buf_object(void)
{
  buf_t *p = utils_safe_malloc(sizeof(buf_t));

  if (!p)
  {
    return NULL;
  }

  p->data = utils_safe_malloc(BUFFER_SIZE);

  if (!p->data)
  {
    utils_safe_free(p);
    return NULL;
  }

  p->size = BUFFER_SIZE;
  p->payload_length = 0;

  return p;
}

void destroy_buf_object(buf_t * b)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s()\n", __func__);
#endif

  if (b)
  {
    // free data
    utils_safe_free(b->data);

    // free b
    utils_safe_free(b);

    b = NULL;
  }
}

void destroy_conn_list(void)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s()\n", __func__);
#endif

  int i;

  for (i = 0; i < global_conn_list_num; i++)
  {
    if (global_conn_list[i])
    {
      // free conn_t
      destroy_conn_object(global_conn_list[i]);

      // the node freed by destroy_conn_object already
      //utils_safe_free(global_conn_list[i]);
      global_conn_list[i] = NULL;
    }
  }

  if (global_conn_list)
  {
    // free list
    free(global_conn_list);
    global_conn_list = NULL;
  }

  global_conn_list_num = -1;
}

//--------------------------------------------------------------------
// Utilities functions
//--------------------------------------------------------------------
void *utils_safe_malloc(uint32_t n)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s(%d)\n", __func__, n);
#endif

  void *p = malloc(n);

  if (p == NULL)
  {
    return NULL;
  }

  return p;
}

void utils_safe_free(void *p)
{
#ifdef _DEBUG_TRACE_
  fprintf(stdout, "call %s(%p)\n", __func__, p);
#endif

  if (p)
  {
    free(p);
    p = NULL;
  }
}

void net_accept(int listening_socket)
{
  //------------------------------------------------------------------
  // accept new connection
  //------------------------------------------------------------------
  int new_connected_socket;
  struct sockaddr_in peer_ipv4_address;
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";

  peer_ipv4_address_length = sizeof(peer_ipv4_address);

  //int accept(int sockfd, struct sockaddr *addr, socklen_t * addrlen);
  if ((new_connected_socket = accept(listening_socket, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
  {
    // failed
    fprintf(stderr, "accept() failed: %s\n", strerror(errno));
    //FIXME: How to do?
  }
  else
  {
    memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));

    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
    inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

    fprintf(stdout, "Accepted a new connection %d from %s:%d\n", new_connected_socket, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

    // create new conn_t object
    conn_t *new_conn_object;

    new_conn_object = create_conn_object();

    if (new_conn_object == NULL)
    {
      fprintf(stderr, "Fatal error: Cannot allocate resource for new connection, give up.\n");
      close(new_connected_socket);
    }
    else
    {
      // attach to global_conn_list
      global_conn_list[new_connected_socket] = new_conn_object;

      net_register_read(new_connected_socket);
      //net_register_write(new_connected_socket);
      //net_register_except(new_connected_socket);
    }
  }
}

int net_read(int fd)
{
  ssize_t n;
  conn_t *current = global_conn_list[fd];

  //ssize_t read(int fd, void *buf, size_t count);
  if ((n = read(fd, current->rbuf->data + current->rbuf->payload_length, current->rbuf->size - current->rbuf->payload_length)) < 0)
  {
    // failed
    fprintf(stderr, "Receive data on socket %d failed: %s\n", fd, strerror(errno));
    // FIXME: How to do?
    return -1;
  }
  else if (n == 0)
  {
    // connection closed by peer.
    fprintf(stdout, "Connection %d closed by peer.\n", fd);

    close(fd);

    destroy_conn_object(current);
    global_conn_list[fd] = NULL;

    net_unregister_read(fd);
    net_unregister_write(fd);
    net_unregister_except(fd);

    return 0;
  }
  else
  {
    current->rbuf->payload_length += n;

    if (current->rbuf->payload_length >= current->rbuf->size)
    {
      // receive buffer is full
      uint32_t new_size = current->rbuf->size * 2;
      char *new_buf = utils_safe_malloc(new_size);

      if (new_size)
      {
	// void *memcpy(void *dest, const void *src, size_t n);
	memcpy(new_buf, current->rbuf->data, current->rbuf->payload_length);
	utils_safe_free(current->rbuf->data);
	current->rbuf->data = new_buf;
	current->rbuf->size = new_size;
      }
      else
      {
	// failed
	// FIXME: allocate memory failed, how to do?
      }
    }

    // TODO: process received data according to application protocol
  }

  return n;
}

int net_write(int fd)
{
  ssize_t n;

  conn_t *c = global_conn_list[fd];
  buf_t *sbuf = c->sbuf;

  //ssize_t write(int fd, const void *buf, size_t count);
  if ((n = write(fd, c->sbuf->data, c->sbuf->payload_length)) < 0)
  {
    // failed
    if (errno == EINTR)
    {
      // FIXME: restart?
    }
    else if (errno == EPIPE)
    {
      // connection closed by peer.
      fprintf(stdout, "Connection %d closed by peer.\n", fd);

      close(fd);

      destroy_conn_object(c);
      global_conn_list[fd] = NULL;

      net_unregister_read(fd);
      net_unregister_write(fd);
      net_unregister_except(fd);
    }
    else
    {
      fprintf(stderr, "Send data to connection %d failed: %s\n", fd, strerror(errno));
    }

    return -1;
  }
  else
  {
    fprintf(stdout, "Sent %d bytes to connection %d.\n", n, fd);

    //void *memmove(void *dest, const void *src, size_t n);
    memmove(sbuf->data, sbuf->data + n, sbuf->payload_length - n);

    sbuf->payload_length -= n;

    if (sbuf->payload_length <= 0)
    {
      net_unregister_write(fd);
    }

    return n;
  }
}

void net_close_all(void)
{
  int i;

  for (i = 0; i < global_conn_list_num; i++)
  {
    if (global_conn_list[i])
    {
      close(i);
    }
  }
}

int buffered_write(int fd, const char *data, unsigned long length)
{
  conn_t *c = global_conn_list[fd];

  if (!c)
  {
    return -1;
  }

  buf_t *sbuf = c->sbuf;

  if (sbuf->payload_length + length > sbuf->size)
  {
    // increase buffer size
    uint32_t new_size = sbuf->payload_length + length;
    char *new_buf = utils_safe_malloc(new_size);

    if (new_size)
    {
      // void *memcpy(void *dest, const void *src, size_t n);
      memcpy(new_buf, sbuf->data, sbuf->payload_length);
      utils_safe_free(sbuf->data);
      sbuf->data = new_buf;
      sbuf->size = new_size;
    }
    else
    {
      // failed
      // FIXME: allocate memory failed, how to do?
    }
  }

  memcpy(sbuf->data + sbuf->payload_length, data, length);
  sbuf->payload_length += length;

  if (sbuf->payload_length > 0)
  {
    net_register_write(fd);
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
