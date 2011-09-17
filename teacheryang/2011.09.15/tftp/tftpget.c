//--------------------------------------------------------------------
// Filename: tftpget.c, get a file from tftp server
// Usage: tftpget <tftp server ip> <tftp server port> <filename>
// Reference: http://www.ietf.org/rfc/rfc1350.txt
//--------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

//--------------------------------------------------------------------
// Macro definition
//--------------------------------------------------------------------
// opcode definition
#define TFTP_OPCODE_RRQ		1
#define TFTP_OPCODE_WRQ		2
#define TFTP_OPCODE_DATA	3
#define TFTP_OPCODE_ACK		4
#define TFTP_OPCODE_ERROR	5

// mode definition
#define TFTP_MODE_NETASCII	"netascii"
#define TFTP_MODE_OCTET		"octet"
#define TFTP_MODE_MAIL		"mail"

#define BUFFER_SIZE		1024

//--------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------
char *global_receive_filename = NULL;
int global_receive_fd = -1;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
void dump_raw_data(const char *buf, int length);
void output_error_message(const char *buf, int length);
int read_data(const char *buf, int length, uint16_t * block_number, int *block_size);
int send_acknowledgment(int fd, struct sockaddr_in *target, uint16_t block_number);

//--------------------------------------------------------------------
// Main function
//--------------------------------------------------------------------
int main(int argc, char **argv)
{
  int fd;
  unsigned short port;
  int finished = 0;

  //------------------------------------------------------------------
  // Parse command line arguments
  //------------------------------------------------------------------
  port = (unsigned short) strtol(argv[2], NULL, 10);

  // char *strdup(const char *s);
  global_receive_filename = strdup(argv[3]);

  //------------------------------------------------------------------
  // step 1, create socket
  //------------------------------------------------------------------
  //int socket(int domain, int type, int protocol);
  if ((fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
  {
    fprintf(stderr, "Failed to create UDP socket: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Created a new UDP socket, fd = %d\n", fd);

  //------------------------------------------------------------------
  // step 2, compose RRQ request 
  //------------------------------------------------------------------

  //------------------------------------------------------------------
  //  RRQ/WRQ packet definition
  //------------------------------------------------------------------
  //
  //   2 bytes   string      1 byte   string    1 byte
  //  +--------+------------+------+------------+-----+
  //  | Opcode |  Filename  |   0  |    Mode    |  0  |
  //  +--------+------------+------+------------+-----+
  //
  //  RRQ: opcode = 1
  //  WRQ: opcode = 2
  //
  //------------------------------------------------------------------

  char request[BUFFER_SIZE];
  int offset;

  // set opcode, in network byte order
  offset = 0;
  uint16_t *op = (uint16_t *) (request + offset);

  *op = htons(TFTP_OPCODE_RRQ);
  offset += 2;

  // set filename
  // FIXME: Make sure the filename's length less than BUFFER_SIZE-2-1-mode length-1
  //void *memcpy(void *dest, const void *src, size_t n);
  memcpy(request + offset, argv[3], strlen(argv[3]));
  offset += strlen(argv[3]);

  *(request + offset) = 0;
  offset += 1;

  // set mode
  memcpy(request + offset, TFTP_MODE_OCTET, strlen(TFTP_MODE_OCTET));
  offset += strlen(TFTP_MODE_OCTET);

  *(request + offset) = 0;
  offset += 1;

#ifdef _DEBUG_
  // Dump request
  fprintf(stdout, "Request: ");
  dump_raw_data(request, offset);
#endif

  //------------------------------------------------------------------
  // step 3, send request to tftp server
  //------------------------------------------------------------------
  struct sockaddr_in peer_ipv4_address;

  memset(&peer_ipv4_address, 0, sizeof(peer_ipv4_address));

  peer_ipv4_address.sin_family = AF_INET;
  peer_ipv4_address.sin_port = htons(port);

  // int inet_pton(int af, const char *src, void *dst);
  inet_pton(AF_INET, argv[1], &peer_ipv4_address.sin_addr);

  ssize_t sent;

  //ssize_t sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
  if ((sent = sendto(fd, request, offset, 0, (struct sockaddr *) &peer_ipv4_address, sizeof(peer_ipv4_address))) < 0)
  {
    // failed
    fprintf(stderr, "Send request to tftp server(%s:%d) failed: %s\n", argv[1], port, strerror(errno));
    close(fd);
    exit(1);
  }
  else
  {
    // success
    fprintf(stdout, "Send request to tftp server(%s:%d) successfully.\n", argv[1], port);
    fprintf(stdout, "Waiting for response ...\n");
  }

  //------------------------------------------------------------------
  // step 4, receive response from tftp server
  //------------------------------------------------------------------
  char response[BUFFER_SIZE];
  socklen_t peer_ipv4_address_length;
  char peer_ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";
  ssize_t received;

  for (;;)
  {
    if (finished > 0)
    {
      fprintf(stdout, "Finished.\n");
      break;
    }

    // value-result parameter, will be modified by recvfrom() calling
    peer_ipv4_address_length = sizeof(peer_ipv4_address);

    //ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t * fromlen);
    if ((received = recvfrom(fd, response, sizeof(response), 0, (struct sockaddr *) &peer_ipv4_address, &peer_ipv4_address_length)) < 0)
    {
      // failed
      fprintf(stderr, "Receive response from tftp server(%s:%d) failed: %s\n", argv[1], port, strerror(errno));
      close(fd);
      exit(1);
    }
    else
    {
      // success
      memset(peer_ipv4_address_string, 0, sizeof(peer_ipv4_address_string));

      //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
      inet_ntop(AF_INET, &peer_ipv4_address.sin_addr, peer_ipv4_address_string, sizeof(peer_ipv4_address_string));

      fprintf(stdout, "Receive %d bytes response from tftp server(%s:%d) successfully.\n", received, peer_ipv4_address_string, ntohs(peer_ipv4_address.sin_port));

#ifdef _DEBUG_
      fprintf(stdout, "Response: ");
      dump_raw_data(response, received);
#endif

      uint16_t response_opcode = ntohs(*(uint16_t *) response);
      uint16_t block_number;
      int block_size;

#ifdef _DEBUG_
      fprintf(stdout, "response_opcode = %d\n", response_opcode);
#endif

      switch (response_opcode)
      {
	case TFTP_OPCODE_ERROR:
	  output_error_message(response, received);
	  exit(1);
	  break;
	case TFTP_OPCODE_DATA:
	  //int read_data(const char *buf, int length, uint16_t *block_number, int *block_size);
	  read_data(response, received, &block_number, &block_size);

	  //int send_acknowledgment(int fd, struct sockaddr_in *target, uint16_t block_number);
	  send_acknowledgment(fd, &peer_ipv4_address, block_number);

	  if (block_size < 512)
	  {
	    // finished
	    close(global_receive_fd);
	    finished = 1;
	  }

	  break;
	default:
	  break;
      }
    }
  }

  //------------------------------------------------------------------
  // Close socket
  //------------------------------------------------------------------
  close(fd);

  //------------------------------------------------------------------
  // Release resources
  //------------------------------------------------------------------
  if (global_receive_filename != NULL)
  {
    free(global_receive_filename);
    global_receive_filename = NULL;
  }

  return 0;
}

void dump_raw_data(const char *buf, int length)
{
  int i;

  for (i = 0; i < length; i++)
  {
    fprintf(stdout, "%02x", buf[i] & 0xff);
  }

  fprintf(stdout, "\n");
}

void output_error_message(const char *buf, int length)
{
  //------------------------------------------------------------------
  // Error package definition
  //------------------------------------------------------------------
  // 
  //  2 bytes     2 bytes      string    1 byte
  // +--------+------------+------------+------+
  // | Opcode |  ErrorCode |   ErrMsg   |   0  |
  // +--------+------------+------------+------+
  // 
  // opcode = 5
  //
  //------------------------------------------------------------------
  uint16_t error_code = ntohs(*(uint16_t *) (buf + 2));	// NBO -> HBO

  fprintf(stderr, "Error code: %d, message: %s\n", error_code, buf + 4);
}

int read_data(const char *buf, int length, uint16_t * block_number, int *block_size)
{
  //------------------------------------------------------------------
  // Data package definition
  //------------------------------------------------------------------
  //
  //  2 bytes     2 bytes      n bytes
  // +--------+------------+------------+
  // | Opcode |   Block #  |   Data     |
  // +--------+------------+------------+
  //
  // opcode = 3
  //
  //------------------------------------------------------------------
  *block_number = ntohs(*(uint16_t *) (buf + 2));	// NBO -> HBO

  fprintf(stdout, "Received block #%02d.\n", *block_number);

  if (global_receive_fd == -1)
  {
    //int open(const char *pathname, int flags, mode_t mode);
    if ((global_receive_fd = open(global_receive_filename, O_WRONLY | O_CREAT | O_EXCL, 0644)) < 0)
    {
      fprintf(stderr, "Open %s file for writing failed: %s\n", global_receive_filename, strerror(errno));
      return -1;
    }
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  write(global_receive_fd, buf + 4, length - 4);

  *block_size = length - 4;

  return 0;
}

int send_acknowledgment(int fd, struct sockaddr_in *target, uint16_t block_number)
{
  //------------------------------------------------------------------
  // ACK packet definition
  //------------------------------------------------------------------
  //
  //  2 bytes     2 bytes
  // +--------+------------+
  // | Opcode |   Block #  |
  // +--------+------------+
  //
  // opcode = 4;
  //------------------------------------------------------------------
  char buf[4];

  uint16_t *opcode = (uint16_t *) buf;	// NBO -> HBO
  uint16_t *number = (uint16_t *) (buf + 2);	// NBO -> HBO

  *opcode = htons(TFTP_OPCODE_ACK);
  *number = htons(block_number);

  //ssize_t sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr * to, socklen_t tolen);
  sendto(fd, buf, 4, 0, (struct sockaddr *) target, sizeof(struct sockaddr_in));

  return 0;
}
