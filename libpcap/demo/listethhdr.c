/**
 * @file listethhdr.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/14 16:12:09
 */

/* Simple Sniffer */
/* To compile: gcc list2.c -o list2 -lpcap */

#include <pcap.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXBYTES2CAPTURE 2048

int hex_print(const u_char *pdata, int plen)
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

void processPacket(u_char *arg, const struct pcap_pkthdr * pkthdr, 
                   const u_char *packet)
{
    int *counter = (int *)arg;

    printf("Packet Count: %d\n", ++(*counter));
    printf("Received Packet Size: %d\n", pkthdr->len);
    printf("Payload: \n");
    hex_print(packet, 18);
    return ;
}

int main(int argc, char *argv[])
{
    int count = 0;
    pcap_t *descr = NULL;
    char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
    
    if (argc < 2) {
        fprintf(stderr, "usage: <devname>\n");
        exit(1);
    }
    device = argv[1];

    memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    printf("Opening device %s\n", device);

    /* Open device in promiscuous mode */
    descr = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 512, errbuf);

    /* Loop forever & call processPacket() for every recevied packet */
    pcap_loop(descr, -1, processPacket, (u_char *)&count);

    return 0;
}

