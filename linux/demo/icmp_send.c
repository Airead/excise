/**
 * @file icmp_send.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/22 10:28:34
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int s, i;
    char buf[80];
    struct ip *ip = (struct ip *)buf;
    struct icmphdr *icmp = (struct icmphdr *)(ip + 1);
    struct sockaddr_in dst;
    char *srcip, *dstip;
    int on;
    int num = 1;
 
    if(argc < 3) {
        printf("\nUsage: %s <saddress> <dstaddress> [number]\n", argv[0]);
        printf("- saddress is the spoofed source address\n");
        printf("- dstaddress is the target\n");
        printf("- number is the number of packets to send, 100 is the default\n");
        exit(1);
    }
    srcip = argv[1];
    dstip = argv[2];

    /* If enough argument supplied */
    if(argc == 4) {
        /* Copy the packet number */
        num = atoi(argv[3]);
    }

    for (i = 0; i < num; i++) {
        
    }
    buf[50] = 1;

    on = 1;
    memset(buf, 0, sizeof(buf));
    if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        fprintf(stderr, "create socket failed: %s\n", strerror(errno));
        exit(1);
    }

    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
        fprintf(stderr, "setsockopt() for IP_HDRINCL failed: %s\n", strerror(errno));
        exit(1);
    }

    if ((ip->ip_src.s_addr = inet_addr(srcip)) == -1) {
        fprintf(stderr, "%s: Can't resolve, unknown host.\n", argv[2]);
        exit(1);
    }
    if ((ip->ip_dst.s_addr = inet_addr(dstip)) == -1) {
        fprintf(stderr, "%s: Can't resolve, unknown host.\n", argv[2]);
        exit(1);
    }

    fprintf(stdout, "Sending to %s from spoofed %s\n", inet_ntoa(ip->ip_dst), srcip);

    /* ip structure */
    ip->ip_v = 4;
    ip->ip_hl = sizeof(*ip) >> 2;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(buf));
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

    if (sendto(s, buf, sizeof(buf), 0, (struct sockaddr *)&dst, sizeof(dst)) < 0) {
        fprintf(stderr, "send failed: %s\n", strerror(errno));
    }

    close(s);
    sleep(2);

    return 0;
}
