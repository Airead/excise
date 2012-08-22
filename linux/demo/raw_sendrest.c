/*** IPPROTO_RAW sender ***/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SRC "192.168.1.12"
#define DEST "192.168.1.245"

uint32_t checksum_partial(unsigned char *buf, int len, uint32_t base)
{
    int i;
    uint16_t *data;
    uint32_t sum = 0;

#undef dprintf
#define dprintf(fmt, args...)  //printf(fmt, ##args)

    if (len % 2 != 0) {
        len--;
        sum += buf[len];
    }
    data = (uint16_t *)buf;

    for (i = 0; i < len / 2; i++) {
        dprintf("[%d] %04x\n", i, data[i]);
        sum += data[i];
    }
    dprintf("sum: %04x\n", sum);

    return sum + base;
}

uint16_t checksum_tcpudp(u_int32_t saddr, u_int32_t daddr, unsigned short len, 
                         unsigned short proto, uint32_t base)
{
    uint32_t sum = 0;

#undef dprintf
#define dprintf(fmt, args...) // printf(fmt, ##args)
    
    sum += saddr & 0xffff;
    dprintf("%04x\n", saddr & 0xffff);
    sum += (saddr >> 16) & 0xffff;
    dprintf("%04x\n", (saddr >> 16) & 0xffff);
    sum += daddr & 0xffff;
    dprintf("%04x\n", daddr & 0xffff);
    sum += (daddr >> 16) & 0xffff;
    dprintf("%04x\n", (daddr >> 16) & 0xffff);
    sum += htons(len);
    dprintf("%04x\n", htons(len));
    sum += htons(proto);
    dprintf("%04x\n", htons(proto));
    dprintf("%x\n", sum);

    sum += base;

    sum = (sum >> 16) + (sum & 0xffff);

    return ~(sum & 0xffff);
}

int main(void)
{

	int s;
	struct sockaddr_in saddr, daddr;
	char packet[1024];
    char *payload;
    char *str;
	/* point the iphdr to the beginning of the packet */
	struct iphdr *ip = (struct iphdr *)packet;  
    struct tcphdr *tcp;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

    saddr.sin_family = AF_INET;
    saddr.sin_port = 0;
    inet_pton(AF_INET, SRC, (struct in_addr *)&saddr.sin_addr.s_addr);
    memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));

	daddr.sin_family = AF_INET;
	daddr.sin_port = 88; /* not needed in SOCK_RAW */
	inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
	memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
	memset(packet, 0, sizeof(packet));   /* payload will be all As */

	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);	/* 16 byte value */
	ip->frag_off = 0;		/* no fragment */
	ip->ttl = 64;			/* default value */
	ip->protocol = IPPROTO_TCP;	/* protocol at L4 */
	ip->check = 0;			/* not needed in iphdr */
	ip->saddr = saddr.sin_addr.s_addr;
	ip->daddr = daddr.sin_addr.s_addr;

    tcp = (struct tcphdr *)(packet + ip->ihl * 4);

    tcp->source = htons(19234);
    tcp->dest = htons(88);
    tcp->seq = htons(2);
    tcp->ack = 1;
    tcp->ack_seq = htons(3);
    tcp->doff = 5;
    tcp->rst = 1;
    tcp->window = htons(4096);
    tcp->check = htons(1);
    
    payload = packet + ip->ihl * 4 + tcp->doff * 4;

    str = "I am Airead Fan";
    memcpy(payload, str, strlen(str));

    tcp->check = 0;
    tcp->check = checksum_tcpudp(ip->saddr, ip->daddr, 1024 - ip->ihl * 4, IPPROTO_TCP,
                                 checksum_partial((unsigned char *)tcp, 1024 - ip->ihl * 4, 0));

	while(1) {
		sleep(1);
		if (sendto(s, (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) < 0)
			perror("packet send error:");
        printf("send a packet, check = %04x\n", tcp->check);
	}
	exit(EXIT_SUCCESS);
}
