/**
 * @file main.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/15 16:00:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>            /* for NF_ACCEPT */
#include <errno.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#include <libnetfilter_queue/libnetfilter_queue.h>

#ifdef __LITTLE_ENDIAN
#define IPQUAD(addr)                            \
    ((unsigned char *)&addr)[0],                \
        ((unsigned char *)&addr)[1],            \
        ((unsigned char *)&addr)[2],            \
        ((unsigned char *)&addr)[3]
#else
#define IPQUAD(addr)                            \
    ((unsigned char *)&addr)[3],                \
        ((unsigned char *)&addr)[2],            \
        ((unsigned char *)&addr)[1],            \
        ((unsigned char *)&addr)[0]
#endif

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

uint16_t checksum_tcpudp(__be32 saddr, __be32 daddr, unsigned short len, 
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

int pkt_handler(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
                struct nfq_data *nfa, void *data)
{
    int id = 0;
    struct iphdr *iph;
    struct tcphdr *tcph;
    struct nfqnl_msg_packet_hdr *ph;
    unsigned char *pdata = NULL;
    unsigned char *payload;
    uint32_t check_partial;
    uint16_t old_check, check;
    int ahl;                    /* all header length */
    int pl;                     /* pdata length */

//    fprintf(stdout, "entering callback\n");

    ph = nfq_get_msg_packet_hdr(nfa);
    if (ph) {
        id = ntohl(ph->packet_id);
//        fprintf(stdout, "hw_protocol=0x%04x hook=%u id=%u\n", ntohs(ph->hw_protocol), ph->hook, id);
    }

    pl = nfq_get_payload(nfa, &pdata);
//    fprintf(stdout, "=================================\n");
//    fprintf(stdout, "pdata len %d\n", pl);
    
    iph = (struct iphdr *)pdata;

//   fprintf(stdout, "receive pkt from %u.%u.%u.%u to %u.%u.%u.%u, iplen %u, iphlen %u, proto %d\n",
//           IPQUAD(iph->saddr), IPQUAD(iph->daddr), ntohs(iph->tot_len), iph->ihl, iph->protocol);

    if (iph->protocol != IPPROTO_TCP) {
        goto pass;
    }

    tcph = (struct tcphdr *)(pdata + iph->ihl * 4);
//    fprintf(stdout, "port from %u to %u, tcphlen: %x\n", ntohs(tcph->source),
//            ntohs(tcph->dest), tcph->doff);
    
    ahl = (iph->ihl + tcph->doff) * 4;
    if (pl - ahl > 0) {
        payload = pdata + ahl;
    } else {
        payload = NULL;
    }

    if (payload != NULL) {
//        fprintf(stdout, "%s\n", payload);
        char *p;
        p = (char *)payload;

//        fprintf(stdout, "%s\n", payload);

        while ((p = strstr((const char *)p, "109")) != NULL) {
            fprintf(stdout, "catch ip: \n");
            write(STDOUT_FILENO, p, strlen("XXX.XXX.XXX.XXX"));
            fprintf(stdout, "\n");
            memcpy(p, "xxx", strlen("xxx"));
//            memset(payload, 'A', pl - ahl);
//            fprintf(stdout, "%s\n", p);
        }
    }

    
    old_check = tcph->check;
    tcph->check = 0;
    check_partial = checksum_partial((unsigned char *)tcph, pl - iph->ihl * 4, 0);
//    fprintf(stdout, "pl - iph->ihl * 4: %d, partial csum: %04x\n", pl - iph->ihl * 4, check_partial);
    check = checksum_tcpudp(iph->saddr, iph->daddr, pl - iph->ihl * 4, 
                            IPPROTO_TCP, check_partial);
    tcph->check = check;
                    

//    fprintf(stdout, "origin check: %04x, my check: %04x, diff: %d\n", tcph->check, check, check - tcph->check);
    
pass:
    return nfq_set_verdict(qh, id, NF_ACCEPT, pl, pdata);

    return 0;
}

int main(int argc, char *argv[])
{
    struct nfq_handle *h;
	struct nfq_q_handle *qh;
	int fd;
	int rv;
	char buf[4096] __attribute__ ((aligned));

    fprintf(stdout, "opening library handle\n");
	h = nfq_open();
	if (!h) {
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

	fprintf(stdout, "unbinding existing nf_queue handler for AF_INET (if any)\n");
	if (nfq_unbind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

	fprintf(stdout, "binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	if (nfq_bind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

	fprintf(stdout, "binding this socket to queue '0'\n");
	qh = nfq_create_queue(h,  0, &pkt_handler, NULL);
	if (!qh) {
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

	fprintf(stdout, "setting copy_packet mode\n");
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	fd = nfq_fd(h);

	for (;;) {
		if ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
//			fprintf(stdout, "pkt received\n");
			nfq_handle_packet(h, buf, rv);
//            memset(buf, 0, sizeof(buf));
			continue;
		}
		/* if your application is too slow to digest the packets that
		 * are sent from kernel-space, the socket buffer that we use
		 * to enqueue packets may fill up returning ENOBUFS. Depending
		 * on your application, this error may be ignored. Please, see
		 * the doxygen documentation of this library on how to improve
		 * this situation.
		 */
		if (rv < 0 && errno == ENOBUFS) {
			fprintf(stdout, "losing packets!\n");
			continue;
		}
		perror("recv failed");
		break;
	}

	fprintf(stdout, "unbinding from queue 0\n");
	nfq_destroy_queue(qh);

#ifdef INSANE
	/* normally, applications SHOULD NOT issue this command, since
	 * it detaches other programs/sockets from AF_INET, too ! */
	fprintf(stdout, "unbinding from AF_INET\n");
	nfq_unbind_pf(h, AF_INET);
#endif

	fprintf(stdout, "closing library handle\n");
	nfq_close(h);

    return 0;
}
