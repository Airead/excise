#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
#if 0
  // defined in /usr/include/netinet/in.h

  /* Internet address.  */
  typedef uint32_t in_addr_t;

  struct in_addr
  {
    in_addr_t s_addr;
  };
#endif

  struct in_addr addr1;
  in_addr_t addr2;

#if 0
  in_addr_t inet_addr(const char *cp);
#endif

  // inet_aton()  converts  the  Internet  host address cp from the
  // standard numbers-and-dots notation into binary data and stores
  // it  in  the  structure that inp points to. inet_aton() returns
  // non-zero if the address is valid, zero if not.

  //int inet_aton(const char *cp, struct in_addr *inp);
  if (inet_aton(argv[1], &addr1) != 0)
  {
    // valid
    //fprintf(stdout, "Value address(in network byte order): 0x%08x", addr1.s_addr);
    fprintf(stdout, "%s -> 0x%08x", argv[1], addr1.s_addr);
  }
  else
  {
    // invalid
    fprintf(stdout, "%s is an invalid address.\n", argv[1]);
    exit(1);
  }

  //The inet_ntoa() function converts the Internet host address in
  //given in network byte order to a string in  standard  numbers-
  //and-dots  notation.   The  string  is returned in a statically
  //allocated buffer, which subsequent calls will overwrite.

  //char *inet_ntoa(struct in_addr in);
  fprintf(stdout, " -> %s\n", inet_ntoa(addr1));

  return 0;
}
