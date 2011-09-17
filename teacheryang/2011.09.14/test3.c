#include <stdio.h>
#include <netdb.h>

int main(int argc, char **argv)
{
  struct servent *s;

#if 0
  struct servent
  {
    char *s_name;		/* official service name */
    char **s_aliases;		/* alias list */
    int s_port;			/* port number */
    char *s_proto;		/* protocol to use */
  }
#endif

  //struct servent *getservbyname(const char *name, const char *proto);
  s = getservbyname("http", NULL);

  if (s)
  {
    fprintf(stdout, "Service name: %s\n", s->s_name);
    fprintf(stdout, "Aliases:\n");

    char **p = s->s_aliases;

    while (p && *p)
    {
      fprintf(stdout, "\t%s\n", *p++);
    }

    fprintf(stdout, "Port number: %d\n", ntohs(s->s_port));
    fprintf(stdout, "Protocol: %s\n", s->s_proto);
  }

  //struct servent *getservbyport(int port, const char *proto);
  s = getservbyport(htons(22), NULL);

  if (s)
  {
    fprintf(stdout, "Service name: %s\n", s->s_name);
    fprintf(stdout, "Aliases:\n");

    char **p = s->s_aliases;

    while (p && *p)
    {
      fprintf(stdout, "\t%s\n", *p++);
    }

    fprintf(stdout, "Port number: %d\n", ntohs(s->s_port));
    fprintf(stdout, "Protocol: %s\n", s->s_proto);
  }

  return 0;
}
