#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  struct in_addr ipv4_address;

  //------------------------------------------------------------------
  // Convert IPv4 address, af = AF_INET
  //------------------------------------------------------------------
  //int inet_pton(int af, const char *src, void *dst);
  if (inet_pton(AF_INET, argv[1], &ipv4_address) < 0)
  {
    if (errno == EAFNOSUPPORT)
    {
      // address family not support
      fprintf(stderr, "address family not support\n");
    }
    else
    {
      // invalid address
      fprintf(stderr, "invalid address\n");
    }
  }
  else
  {
    fprintf(stdout, "%s -> 0x%08x", argv[1], ipv4_address.s_addr);

    //char ipv4_address_string[INET_ADDRSTRLEN+1];
    char ipv4_address_string[] = "xxx.xxx.xxx.xxx\0";

    memset(ipv4_address_string, 0, sizeof(ipv4_address_string));

    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
    inet_ntop(AF_INET, &ipv4_address, ipv4_address_string, sizeof(ipv4_address_string));

    fprintf(stdout, " -> %s\n", ipv4_address_string);
  }

  //------------------------------------------------------------------
  // Convert IPv6 address, af = AF_INET6
  //------------------------------------------------------------------
  struct in6_addr ipv6_address;

#if 0
// IPv6 address, defined in /usr/include/netinet/in.h
  struct in6_addr
  {
    union
    {
      uint8_t u6_addr8[16];
      uint16_t u6_addr16[8];
      uint32_t u6_addr32[4];
    } in6_u;
#  define s6_addr		in6_u.u6_addr8
#  define s6_addr16		in6_u.u6_addr16
#  define s6_addr32		in6_u.u6_addr32
  };
#endif

  // fe80::20d:60ff:fecb:86e5
  //int inet_pton(int af, const char *src, void *dst);
  if (inet_pton(AF_INET6, "fe80::20d:60ff:fecb:86e5", &ipv6_address) < 0)
  {
    if (errno == EAFNOSUPPORT)
    {
      // address family not support
      fprintf(stderr, "address family not support\n");
    }
    else
    {
      // invalid address
      fprintf(stderr, "invalid address\n");
    }
  }
  else
  {
    fprintf(stdout, "fe80::20d:60ff:fecb:86e5 -> ");

    int i;

    for (i = 0; i < 16; i++)
    {
      fprintf(stdout, "%02x", ipv6_address.s6_addr[i]);
    }

    //fprintf(stdout, "\n");

    char ipv6_address_string[INET6_ADDRSTRLEN + 1];

    memset(ipv6_address_string, 0, sizeof(ipv6_address_string));

    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
    inet_ntop(AF_INET6, &ipv6_address, ipv6_address_string, sizeof(ipv6_address_string));

    fprintf(stdout, " -> %s\n", ipv6_address_string);
  }

  return 0;
}
