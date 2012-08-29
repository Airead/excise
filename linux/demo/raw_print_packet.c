/**
 * @file raw_print_packet.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/29 15:54:57
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <linux/if_ether.h>

int main(int argc, char *argv[])
{
    int s;
    struct ethhdr *ethh;
    struct iphdr *iph;
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr;
	char packet[4096];
    int count;
    unsigned int tcplen;
    int i;

	if ((s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);
    int opt = 0;

    count = 0;
	while(1) {
		if ((rn = recvfrom(s, (char *)&packet, sizeof(packet), 0,
                           (struct sockaddr *)&saddr, &fromlen)) < 0) {
			perror("packet receive error:");
        }
        if (rn == 0) {
            printf("the peer has performed an orderly shutdown\n");
            break;
        }
        
        ethh = (struct ethhdr *)packet;
        if (ethh->h_proto != htons(ETH_P_IP)) {
            continue;
        }
        
        iph = (struct iphdr *)(packet + sizeof(struct ethhdr));
        
        if (iph->protocol == IPPROTO_TCP) {
            tcplen = ntohs(iph->tot_len) - iph->ihl * 4;
            printf("tcp packet len: %u\n", tcplen);
        }
	}
    
    return 0;
}
