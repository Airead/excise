/**
 * @file raw_print_pkt.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/22 12:35:22
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

#if 0
0000   00 0c 29 cd 58 d7 20 6a 8a 64 eb 84 08 00 45 00  ..).X. j.d....E.
0010   04 00 f5 96 00 00 40 06 fd 0f c0 a8 01 0c c0 a8  ......@.........
0020   01 f5 4b 22 00 58 00 02 00 00 00 03 00 00 50 14  ..K".X........P."
#endif

int hex_print(char *pdata, int plen)
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
            fprintf(stdout, "%02x ", pdata[i]);
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

int main(int argc, char *argv[])
{
    int s;
    ssize_t rn;                 /* receive number */
	struct sockaddr_in saddr;
	char packet[4096];
    int count;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	socklen_t fromlen = sizeof(saddr);
    int opt;

    count = 0;
	while(1) {
		if ((rn = recvfrom(s, (char *)&packet, sizeof(packet), 0,
                           (struct sockaddr *)&saddr, &fromlen)) < 0)
			perror("packet receive error:");
        if (rn == 0) {
            printf("the peer has performed an orderly shutdown\n");
            break;
        }

        printf("rn = %lu \n", rn);
        printf("[%d]\n", count++);
        hex_print(packet, rn);
        printf("\n");

        if (count == 16) {
            if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt)) < 0) {
                perror("setsocketopt failed");
            } else {
                fprintf(stdout, "setsocketopt successful\n");
            }
            // int shutdown(int sockfd, int how);
            /* if (shutdown(s, SHUT_RD) < 0) {
             *     perror("shutdown failed");
             * } */
        }
	}
    
    return 0;
}
