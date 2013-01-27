/**
 * @file icmp_rcv_all.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/22 09:51:52
 */

#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>

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

int main(int argc, char *argv[])
{
    int s;
//    struct ethhdr *ethh;
    struct iphdr *iph;
    struct icmphdr *icmph;
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr;
	socklen_t fromlen;
    char packet[4096];

    if ((s = socket(PF_PACKET, SOCK_RAW, ntohs(ETH_P_IP))) < 0) {
        fprintf(stderr, "create raw socket failed: %s\n", strerror(errno));
        exit(1);
    }

    memset(packet, 0, sizeof(packet));
    fromlen = sizeof(saddr);

    while (1) {
        if ((rn = recvfrom(s, (char *)&packet, sizeof(packet), 0,
                           (struct sockaddr *)&saddr, &fromlen)) < 0) {
            fprintf(stderr, "recvfrom failed: %s\n", strerror(errno));
        }
        if (rn == 0) {
            fprintf(stdout, "the peer has performed an orderly shutdown\n");
            break;
        }
//        ethh = (struct ethhdr *)packet;
        iph = (struct iphdr *)(packet + sizeof(struct ethhdr));
        if (iph->protocol != IPPROTO_ICMP) {
            continue;
        }
        fprintf(stdout, "=================================\n");
        fprintf(stdout, "receive packet: %lu\n", rn);
        fprintf(stdout, "recevie icmp\n");
        // hex_print(packet, rn);
        icmph = (struct icmphdr *)(packet + sizeof(struct ethhdr) + iph->ihl * 4);
        fprintf(stdout, "type %u, code %u\n", icmph->type, icmph->code);
        fprintf(stdout, "checksum 0x%04x, \n", icmph->checksum);
        fprintf(stdout, "id %u, sequence %u\n", ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));
    }
    
    return 0;
}
