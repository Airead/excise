#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

extern int h_errno;

int main(int argc, char **argv)
{
  struct hostent *h;

  //struct hostent *gethostbyname(const char *name);
  h = gethostbyname(argv[1]);

  if (h == NULL)
  {
    fprintf(stderr, "Failed to resolv domain name %s: %s\n", argv[1], hstrerror(h_errno));
    exit(1);
  }

#if 0
  struct hostent
  {
    char *h_name;		/* official name of host */
    char **h_aliases;		/* alias list */
    int h_addrtype;		/* host address type */
    int h_length;		/* length of address */
    char **h_addr_list;		/* list of addresses */
  }
#  define h_addr  h_addr_list[0]	/* for backward compatibility */
#endif

  fprintf(stdout, "Official name: %s\n", h->h_name);

  fprintf(stdout, "Aliases: \n");

  char **p;

  p = h->h_aliases;

  while (p && *p)
  {
    fprintf(stdout, "\t%s\n", *p);
    p++;
  }

  if (h->h_addrtype == AF_INET)
  {
    fprintf(stdout, "Address type: IPv4\n");
  }
  else
  {
    fprintf(stdout, "Address type: IPv6\n");
  }

  fprintf(stdout, "Address length: %d\n", h->h_length);

  fprintf(stdout, "Address:\n");

  p = h->h_addr_list;

  char ip_address_string[INET6_ADDRSTRLEN + 1];

  while (p && *p)
  {
    memset(ip_address_string, 0, sizeof(ip_address_string));

    //const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
    inet_ntop(h->h_addrtype, *p, ip_address_string, sizeof(ip_address_string));

    fprintf(stdout, "\t%s\n", ip_address_string);

    p++;
  }

  return 0;
}
