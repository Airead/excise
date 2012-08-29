/*** IPPROTO_RAW receiver ***/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	int s;
    int count;
	struct sockaddr_in saddr;
	char packet[4096];

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);

    count = 0;
	while(1) {
		if (recvfrom(s, (char *)&packet, sizeof(packet), 0,
                     (struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");

        printf("%d\n", count++);

        printf("=================================\n");
		int i = sizeof(struct iphdr);	/* print the payload */
		while (i < sizeof(packet)) {
			fprintf(stderr, "%c", packet[i]);
			i++;
		}
		printf("\n");

	}
	exit(EXIT_SUCCESS);
}
