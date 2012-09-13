/**
 * @file ircsniper.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/11 14:52:11
 */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#define PKT_BUF 4096

#if 0
int set_promisc(char * interface, int sock)
{ 
    struct ifreq ifr; 

    strcpy(ifr.ifr_name,interface); 
    if (ioctl(sock,SIOCGIFFLAGS,&ifr) == -1){ 
        printf( "Could not receive flags for the interface.\n "); 
        return -1;
    } 

    ifr.ifr_flags |= IFF_PROMISC; 
    if(ioctl(sock,SIOCGIFFLAGS,&ifr) == -1){ 
        printf( "Could not set the PROMISC flag.\n "); 
        return -1;
    } 
    printf( "Setting interface ::: %s ::: to promisc\n ",interface); 

    return 0;
} 

void handler_servmsg(char *buf, int len)
{
    char *p, *origin, *cmd, *peer, *content;

    fprintf(stdout, "handler servmsg\n");
    write(STDOUT_FILENO, buf, len);

    p = strtok(buf, ":");

    origin = strtok(NULL, "!");
    if (origin == NULL || origin - buf >= len) 
        goto out;

    p = strtok(NULL, " ");
    if (p == NULL || p - buf >= len) {
        goto out;
    }

    cmd = strtok(NULL, " ");
    if (strncmp(cmd, "PRIVMSG", strlen(cmd)) != 0) {
        goto out;
    }
    if (cmd == NULL || cmd - buf >= len) {
        goto out;
    }

    peer = strtok(NULL, ":");
    if (peer == NULL || peer - buf >= len) {
        goto out;
    }
    
    content = peer + strlen(peer) + 1;
    if (content == NULL || content - buf >= len) {
        goto out;
    }

    fprintf(stdout, "%s-->%s: ", origin, peer);
    fflush(stdout);
    write(STDOUT_FILENO, content, len - (content - buf));

out:
    return ;
}

void handler_climsg(char *buf, int len)
{
    
}

static int get_line(char *buf, int len, int *llen)
{
    char *p;
    
    p = buf;
    *llen = 0;
    while (*llen < len && *p != '\r' && *p != '\n') {
        p++;
        (*llen)++;
    }
    
    return 0;
}
#endif

int main(int argc, char *argv[])
{
	int s, os;                  /* os for kernel 2.6.32-279.5.2.el6.centos.plus.x86_64 */
    int datalen;
    int ahl;
    ssize_t rn;
    char *data;
    char *ifname;
    struct ethhdr *ethh;
    struct iphdr *iph;
    struct tcphdr *tcph;
	struct sockaddr_in saddr;
	char packet[PKT_BUF];
    char saddr_str[INET6_ADDRSTRLEN];
    char daddr_str[INET6_ADDRSTRLEN];

    if (argc < 2) {
        fprintf(stderr, "usage: %s <ifname>\n", argv[0]);
        exit(1);
    }
    ifname = argv[1];
    
	if ((s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

    os = s;

	memset(packet, 0, sizeof(packet));
//	socklen_t *len = (socklen_t *)sizeof(saddr);
	socklen_t fromlen = sizeof(saddr);

    while(1) {
        if ((rn = recvfrom(s, (char *)&packet, sizeof(packet), 0,
                           (struct sockaddr *)&saddr, &fromlen)) < 0) {
            perror("packet receive error");
            break;
        }
        s = os;                 /* strange: recvfrom maybe change s */

        if (rn == 0) {
            printf("the peer has performed an orderly shutdown\n");
            break;
        }

        ethh = (struct ethhdr *)packet;
        if (ethh->h_proto != htons(ETH_P_IP)) {
            continue;
        }

        iph = (struct iphdr *)(packet + sizeof(struct ethhdr));
        if (iph->protocol != IPPROTO_TCP) {
            continue;
        }

        /* the port of irc will always larger than 1024 */
        tcph = (struct tcphdr *)((char *)iph + iph->ihl * 4);
        if (ntohs(tcph->source) < 6660 || ntohs(tcph->dest) < 6660) {
            continue;
        }

        //const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
        inet_ntop(AF_INET, &iph->saddr, saddr_str, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET, &iph->daddr, daddr_str, INET6_ADDRSTRLEN);

        tcph = (struct tcphdr *)((char *)iph + iph->ihl * 4);
        ahl = sizeof(struct ethhdr) + iph->ihl * 4 + tcph->doff * 4;
        data = packet + ahl;
        datalen = rn - ahl;

        if (data[0] == ':') {
            write(STDOUT_FILENO, saddr_str, strlen(saddr_str));
            write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, daddr_str, strlen(daddr_str));
            write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, data, datalen);
        } else if (
            (data[0] == 'P' && data[1] == 'R') || /* PRIVMSG */
            (data[0] == 'N' && data[1] == 'i')    /* NickServ */
            ) {
            write(STDOUT_FILENO, saddr_str, strlen(saddr_str));
            write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, daddr_str, strlen(daddr_str));
            write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, data, datalen);
        }
        memset(packet, 0, sizeof(packet));
    }
    return 0;
}
