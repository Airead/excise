/* Simple ARP Sniffer. */
/* Run as root */

#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/* ARP Header, (assuming Ethernet + IPV4 */
#define ARP_REQUEST 1           /* ARP Request */
#define ARP_REPLY 2             /* ARP Reply */

typedef struct arphdr {
    u_int16_t htype;            /* Hardware Type */
    u_int16_t ptype;            /* Protocol Type */
    u_char hlen;                /* Hardware Address Length */
    u_char plen;                /* Protocol Address Length */
    u_int16_t oper;            /* Operation Code */
    u_char sha[6];              /* Sender hardware address */
    u_char spa[4];              /* Sender IP address */
    u_char tha[6];              /* Target hardware address */
    u_char tpa[4];              /* Target IP address */
} arphdr_t;

#define MAXBYTES2CAPTURE 2048

int main(int argc, char *argv[])
{
    int i = 0;
    bpf_u_int32 mask = 0; /* To Store network address and netmask */
    struct bpf_program filter;         /* Place to store the BPF filter program */
    char errbuf[PCAP_ERRBUF_SIZE];     /* Error buff */
    pcap_t *descr = NULL;              /* Network interface handler */

    struct pcap_pkthdr pkthdr;  /* Packet information (timestamp,size...) */
    const unsigned char *packet = NULL; /* Received raw data */
    arphdr_t *arpheader = NULL;         /* Pointer to the ARP header */
    
    memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <interface>\n", argv[0]);
        exit(1);
    }

    /* Open network device for packet capture */
    descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0, 512, errbuf);
    if (descr == NULL) {
        fprintf(stderr, "open live failed: %s\n", errbuf);
        exit(1);
    }
    printf("open %s successful, descr: %p\n", argv[1], descr);

    /* Compiles the filter expression into a BPF filter program */
    pcap_compile(descr, &filter, "arp", 1 ,mask);

    /* Load the fiter program into the packet capture device. */
    pcap_setfilter(descr, &filter);

    while (1) {
        packet = pcap_next(descr, &pkthdr); /* Get one packet */

        if (packet == NULL) {
            continue;
        }

        arpheader = (struct arphdr *)(packet + 14); /* Point to the ARP header */
        printf("\n\nReceived Packet Size: %d bytes\n", pkthdr.len);
        printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ? "Ethernet" : "Unknown");
        printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ? "IPv4" : "Unknown");
        printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST) ? "ARP Request" : "ARP Reply");

        if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x800) {
            printf("Sender MAC: ");
            for (i = 0; i < 6; i++) printf("%02X:", arpheader->sha[i]);
            printf("\nSender IP: ");
            for (i = 0; i < 4; i++) printf("%d.", arpheader->spa[i]);
            printf("\nTarget MAC: ");
            for (i = 0; i < 6; i++) printf("%02X:", arpheader->tha[i]);
            printf("\nTarget IP: ");
            for (i = 0; i < 4; i++) printf("%d.", arpheader->tpa[i]);
            printf("\n");
        }
    }
        return 0;
}
