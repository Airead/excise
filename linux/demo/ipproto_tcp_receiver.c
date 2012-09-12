/*** IPPROTO_RAW receiver ***/
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ip.h>
#include <linux/tcp.h>


int main(void)
{
	int s;
    int count;
    int datalen;
    int ahl;
    ssize_t rn;
    char *data;
    struct iphdr *iph;
    struct tcphdr *tcph;
	struct sockaddr_in saddr;
	char packet[4096];

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
//	socklen_t *len = (socklen_t *)sizeof(saddr);
	socklen_t fromlen = sizeof(saddr);

    count = 0;
	while(1) {
		if ((rn = recvfrom(s, (char *)&packet, sizeof(packet), 0,
                           (struct sockaddr *)&saddr, &fromlen)) < 0)
			perror("packet receive error:");

        
        iph = (struct iphdr *)packet;
        tcph = (struct tcphdr *)((char *)iph + iph->ihl * 4);
        ahl = iph->ihl * 4 + tcph->doff * 4;
        data = packet + ahl;
        datalen = rn - ahl;

        printf("=================================\n");
        printf("[%d] rn: %lu, datalen: %d\n", count++, rn, datalen);
        write(STDOUT_FILENO, data, datalen);
		printf("\n");

	}
	exit(EXIT_SUCCESS);
}
