/* Simple Sniffer */
/* To compile: gcc list2.c -o list2 -lpcap */

#include <pcap.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXBYTES2CAPTURE 2048

void processPacket(u_char *arg, const struct pcap_pkthdr * pkthdr, 
                   const u_char *packet)
{
    int i = 0, *counter = (int *)arg;

    printf("Packet Count: %d\n", ++(*counter));
    printf("Received Packet Size: %d\n", pkthdr->len);
    printf("Payload: \n");
    for (i = 0; i < pkthdr->len; i++) {
        if (isprint(packet[i])) {
            printf("%c", packet[i]);
        } else {
            printf(".");
        }

        if ((i % 16 == 0 && i != 0) || i == pkthdr->len -1) {
            printf("\n");
        }
    }
    return ;
}

int main()
{
    int count = 0;
    pcap_t *descr = NULL;
    char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
    
    memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    /* Get the name of the first device suitable for capture */
    device = pcap_lookupdev(errbuf);
    if (device == NULL) {
        fprintf(stderr, "get device failed: %s\n", strerror(errno));
        exit(1);
    }
    printf("Opening device %s\n", device);

    /* Open device in promiscuous mode */
    descr = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 512, errbuf);

    /* Loop forever & call processPacket() for every recevied packet */
    pcap_loop(descr, -1, processPacket, (u_char *)&count);

    return 0;
}

