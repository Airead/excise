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
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <linux/icmp.h>

#define PACKET_SIZE 4096

static struct ethhdr *ethh;
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

u_short checksum(u_short *data,int len)
{
    u_long sum=0;
    for (;len>1;len-=2) {
        sum+=*data++;
        if(sum & 0x80000000)
            sum=(sum & 0xffff)+(sum>>16);
    }
    if (len==1) {
        u_short i=0;
        *(u_char*)(&i)=*(u_char*)data;
        sum+=i;
    }
    while (sum>>16) {
        sum=(sum & 0xffff)+(sum>>16);
    }
    return (sum==0xffff)?sum:~sum;
}

ssize_t receive_packet(int sockfd, char *packet, struct sockaddr_in *saddr)
{
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr_tmp;
	socklen_t fromlen;

    memset(packet, 0, PACKET_SIZE);
    fromlen = sizeof(saddr_tmp);

    if ((rn = recvfrom(sockfd, packet, PACKET_SIZE, 0,
                       (struct sockaddr *)&saddr_tmp, &fromlen)) < 0) {
        fprintf(stderr, "recvfrom failed: %s\n", strerror(errno));
    }
    if (rn == 0) {
        fprintf(stdout, "the peer has performed an orderly shutdown\n");
    }
    
    *saddr = saddr_tmp;

    return rn;
}

int trans_icmp(char *packet)
{
    char from[INET_ADDRSTRLEN];

    ethh = (struct ethhdr *)packet;
    iph = (struct iphdr *)(packet + sizeof(struct ethhdr));
    if (iph->protocol != IPPROTO_ICMP) {
        goto failed;
    }
    //fprintf(stdout, "recevie icmp\n");
    icmph = (struct icmphdr *)(packet + sizeof(struct ethhdr) + iph->ihl * 4);
    if (icmph->type != ICMP_ECHO && icmph->type != ICMP_ECHOREPLY) {
        goto failed;
    }

    fprintf(stdout, "=================================\n");
     // inet_ntop(AF_INET, &saddr_tmp.sin_addr, from, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &iph->saddr, from, INET_ADDRSTRLEN);
    fprintf(stdout, "receive icmp from: %s\n", from);
    // hex_print(packet, rn);
    fprintf(stdout, "type %u, code %u\n", icmph->type, icmph->code);
    // fprintf(stdout, "checksum 0x%04x, \n", icmph->checksum);
    // fprintf(stdout, "id %u, sequence %u\n", ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));
    return 0;
failed:
    return -1;
    
}

static int make_echoreply(ssize_t len)
{
    __be32 addr;

    addr = iph->saddr;
    iph->saddr = iph->daddr;
    iph->daddr = addr;
    iph->check = 0;

    icmph->type = ICMP_ECHOREPLY;
    icmph->checksum = 0;
    icmph->checksum = checksum((u_short *)icmph, len - sizeof(struct ethhdr) - (iph->ihl << 2));
        
    return 0;
}

int main(int argc, char *argv[])
{
    int sr, ss;                 /* socket receive/send */
    char packet[PACKET_SIZE];
    unsigned long rn;
    struct sockaddr_in src, dst;
    char dstip[INET_ADDRSTRLEN];
    int on;
 
    memset(packet, 0, PACKET_SIZE);

    if ((sr = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
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
        if ((rn = receive_packet(sr, packet, &src)) == -1) {
            fprintf(stderr, "receive_packet failed: %s\n", strerror(errno));
            break;
        }
        if (trans_icmp(packet) < 0) {
            continue;
        }
        if (icmph->type == ICMP_ECHOREPLY) {
            continue;
        }

        make_echoreply(rn);

        dst.sin_addr.s_addr = iph->daddr;
        dst.sin_family = AF_INET;

        inet_ntop(AF_INET, &dst.sin_addr, dstip, INET_ADDRSTRLEN);
        fprintf(stdout, "send ping reply to %s, %lu bytes\n", dstip, rn);
        if (sendto(ss, iph, rn - sizeof(struct ethhdr), 0, (struct sockaddr *)&dst, sizeof(dst)) < 0) {
            fprintf(stderr, "send failed: %s\n", strerror(errno));
        }
        
    }

    close(sr);
    close(ss);

    return 0;
}
