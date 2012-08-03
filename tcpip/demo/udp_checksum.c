/**
 * @file udp_checksum.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/03 09:25:59
 */


#if 0                           /* frame 138 bytes */
0000   20 6a 8a 64 eb 84 00 00 00 00 00 00 08 00 45 00
0010   00 7c 7a 00 00 00 20 11 5e bd 00 00 00 00 c0 a8
0020   01 0c 00 58 04 af 00 68 0d b7 49 20 61 6d 20 41
0030   69 72 65 61 64 20 46 61 6e 00 00 00 00 00 00 00
0040   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0050   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0060   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0070   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0080   00 00 00 00 00 00 00 00 00 00

ip :                                             45 00

          0c
src:                                 00 00 00 00
dst:                                             c0 a8
       01 0c
udp:         00                   b7
len:                      00 68
data:                                49
                                  00
udp checksum:                 0d  b7  *wrong!*
#endif

#include <stdio.h>
#include <stdint.h>

static uint16_t data[] = {
    0x0000, 0x0000, /* src ip */
    0xc0a8, 0x010c, /* dst ip */
    0x0011,         /* protocol */
    0x0068,         /* udp length */
    0x0058, 0x04af, 0x0068, 0x0000, /* udp header */
    0x4920, 0x616d, 0x2041, 0x6972, /* udp data */
    0x6561, 0x6420, 0x4661, 0x6e00,
};

void print16(unsigned short s)
{
    int i, enter;
    
    enter = 0;
    for (i = 15; i>= 0; i--) {
        if (s & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
        enter++;
        if (enter %4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

unsigned short checksum(unsigned short *addr, int count)
{
    unsigned long sum = 0;
    int i;

    for (i = 0; i < count; i++) {
        printf("sum     , %04x: ", (unsigned short)sum);
        print16(sum);
        printf("addr[%d] , %04x: ", i, addr[i]);
        print16(addr[i]);
        sum += addr[i];
        printf("----------------------------\n");
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
    }
    printf("sum     , %04x: ", (unsigned short)sum);
    print16(sum);

    return ~sum;
}

int main(int argc, char *argv[])
{
    unsigned short check;

    check = checksum((unsigned short *)data, sizeof(data) / sizeof(uint16_t));
    printf("check = %04x\n", (unsigned short)check);
    
    check = checksum((unsigned short *)data, 6);
    printf("partial check = %04x\n", (unsigned short)check);

    return 0;
}




