/**
 * @file raw_print_tcp_opt.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/30 17:46:40
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
#include <linux/tcp.h>
#include <linux/if_ether.h>

/*
 *	TCP option
 */
 
#define TCPOPT_NOP		1	/* Padding */
#define TCPOPT_EOL		0	/* End of options */
#define TCPOPT_MSS		2	/* Segment size negotiating */
#define TCPOPT_WINDOW		3	/* Window scaling */
#define TCPOPT_SACK_PERM        4       /* SACK Permitted */
#define TCPOPT_SACK             5       /* SACK Block */
#define TCPOPT_TIMESTAMP	8	/* Better RTT estimations/PAWS */
#define TCPOPT_MD5SIG		19	/* MD5 Signature (RFC2385) */

/*
 *     TCP option lengths
 */

#define TCPOLEN_MSS            4
#define TCPOLEN_WINDOW         3
#define TCPOLEN_SACK_PERM      2
#define TCPOLEN_TIMESTAMP      10
#define TCPOLEN_MD5SIG         18

uint16_t tcp_parse_options(struct tcphdr *th)
{
	unsigned char *ptr;
	int length = (th->doff * 4) - sizeof(struct tcphdr);
    uint16_t in_mss = 0;

	ptr = (unsigned char *)(th + 1);

	while (length > 0) {
		int opcode = *ptr++;
		int opsize;
        
		switch (opcode) {
		case TCPOPT_EOL:
			return -1;
		case TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			continue;
		default:
            opsize = *ptr++;
			if (opsize < 2) /* "silly options" */
				return -1;
			if (opsize > length)
				return -1;	/* don't parse partial options */
			switch (opcode) {
			case TCPOPT_MSS:
				if (opsize == TCPOLEN_MSS) {
//					u16 in_mss = get_unaligned_be16(ptr);
                    in_mss = *((uint16_t *)ptr);
                }
				break;
			case TCPOPT_WINDOW:
				break;
			case TCPOPT_TIMESTAMP:
				break;
			case TCPOPT_SACK_PERM:
				break;
			case TCPOPT_SACK:
				break;
				break;
			}

			ptr += opsize-2;
			length -= opsize;
		}
	}

    return in_mss;
}

int main(int argc, char *argv[])
{
    int s;
    struct ethhdr *ethh;
    struct iphdr *iph;
    struct tcphdr *tcph;
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr;
	char packet[4096];
    int count;
    unsigned int tcplen;
    uint16_t in_mss;

    if (argc < 3) {
        fprintf(stderr, "usage: %s [num_mtu] [num_mss]\n", argv[0]);
        exit(1);
    }

//    checklen = strtoul(argv[1], NULL, 10);
//    msslen = strtoul(argv[2], NULL, 10);

	if ((s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t fromlen = sizeof(saddr);

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
            tcph = (struct tcphdr *)((char *)iph + iph->ihl * 4);
            in_mss = tcp_parse_options(tcph);
            tcplen = ntohs(iph->tot_len) - iph->ihl * 4;
            if (argc > 3) {
                if (in_mss > 0) {
                    printf("[%d] tcp packet len: %u, mss: %u\n ", count++, tcplen, ntohs(in_mss));
                }
            } else {
                printf("[%d] tcp packet len: %u\n", count++, tcplen);
            }
        }
	}
    
    return 0;
}
