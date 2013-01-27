/**
 * @file icmp_rcv.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/21 17:06:25
 */

#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/icmp.h>

#define PACKET_SIZE 4096

static struct iphdr *iph;
static struct icmphdr *icmph;

int hex_print(char *pdata, int plen)
{
    int count;
    
    count = 0;
    while (count < plen) {
        int i;
        fprintf(stdout, "%04x  ", count); /* 0000 */
        for (i = count; i < count + 16; i++) { /*  */
            if (i == count + 8) {
                fprintf(stdout, " ");
            }
            fprintf(stdout, "%02x ", pdata[i] & 0xff);
        }
        fprintf(stdout, "   ");
        for (i = count; i < count + 16; i++) { /*  */
            if (i == count + 8) {
                fprintf(stdout, " ");
            }
            if (isprint(pdata[i])) {
                fputc(pdata[i], stdout);
            } else {
                fputc('.', stdout);
            }
        }
        fputc('\n', stdout);
        count += 16;
    }

    return 0;
}

int recevie_icmp_echo(int sockfd, char *packet, unsigned int *len, struct sockaddr_in *saddr)
{
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr_tmp;
	socklen_t fromlen;
    char from[INET_ADDRSTRLEN];

    memset(packet, 0, PACKET_SIZE);
    fromlen = sizeof(saddr_tmp);

    if ((rn = recvfrom(sockfd, packet, PACKET_SIZE, 0,
                       (struct sockaddr *)&saddr_tmp, &fromlen)) < 0) {
        fprintf(stderr, "recvfrom failed: %s\n", strerror(errno));
    }
    if (rn == 0) {
        fprintf(stdout, "the peer has performed an orderly shutdown\n");
        goto out;
    }
    fprintf(stdout, "=================================\n");
    inet_ntop(AF_INET, &saddr_tmp.sin_addr, from, INET_ADDRSTRLEN);
    fprintf(stdout, "receive packet: %lu, from: %s\n", rn, from);
    // hex_print(packet, rn);
    iph = (struct iphdr *)packet;
    if (iph->protocol == IPPROTO_ICMP) {
        fprintf(stdout, "recevie icmp\n");
    }
    icmph = (struct icmphdr *)(packet + iph->ihl * 4);
    fprintf(stdout, "type %u, code %u\n", icmph->type, icmph->code);
    fprintf(stdout, "checksum 0x%04x, \n", icmph->checksum);
    fprintf(stdout, "id %u, sequence %u\n", ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));
    *len = rn;
out:    
    return 0;
}

int main(int argc, char *argv[])
{
    int sr, ss;                 /* socket receive/send */
    char packet[PACKET_SIZE];
    unsigned int len;
    struct sockaddr_in src, dst;
    char *srcip, *dstip;
    int on;
 
    memset(packet, 0, PACKET_SIZE);

    if ((sr = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        fprintf(stderr, "create raw socket failed: %s\n", strerror(errno));
        exit(1);
    }

    if ((ss = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        fprintf(stderr, "create socket failed: %s\n", strerror(errno));
        exit(1);
    }

    on = 1;
    if (setsockopt(ss, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
        fprintf(stderr, "setsockopt() for IP_HDRINCL failed: %s\n", strerror(errno));
        exit(1);
    }

    while (1) {
        __be32 addr;
        recevie_icmp_echo(sr, packet, &len, &src);
        addr = iph->saddr;
        iph->saddr = iph->daddr;
        iph->daddr = addr;

        dst.sin_addr.s_addr = iph->daddr;
        dst.sin_family = AF_INET;

        icmph->type = ICMP_ECHOREPLY;
        icmph->code = 0;
        icmph->checksum = htons(~(ICMP_ECHO << 8));
#if 0
        /* ip structure */
        ip->ip_v = 4;
        ip->ip_hl = sizeof(*ip) >> 2;
        ip->ip_tos = 0;
        ip->ip_len = htons(PACKET_SIZE);
        ip->ip_id = htons(4321);
        ip->ip_off = htons(0);
        ip->ip_ttl = 255;
        ip->ip_p = 1;
        ip->ip_sum = 0;             /* Let kernel fills in */

        dst.sin_addr = ip->ip_dst;
        dst.sin_family = AF_INET;

        icmp->type = ICMP_ECHO;
        icmp->code = 0;
        icmp->checksum = htons(~(ICMP_ECHO << 8));
#endif
        if (sendto(ss, packet, len, 0, (struct sockaddr *)&dst, sizeof(dst)) < 0) {
            fprintf(stderr, "send failed: %s\n", strerror(errno));
        }
    }

    close(sr);
    close(ss);

    return 0;
}
