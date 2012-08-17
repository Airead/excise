/**
 * @file tcp_checksum.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/03 16:51:55
 */

#if 0
checksum: 0xd0db, should be 0x3437

0000   20 6a 8a 64 eb 84 00 0c 29 cd 58 d7 08 00 45 00   j.d....).X...E.
0010   00 2d 7a 00 00 00 20 06 78 12 3d 87 a9 7d c0 a8  .-z... .x.=..}..
0020   01 0c 00 50 d2 3e ce a7 d7 33 9f e2 04 c6 50 18  ...P.>...3....P.
0030   19 20 d0 db 00 00 48 54 54 50 00 00              . ....HTTP..

ip :                                 3d
          0c
src:                                 3d 87 a9 7d 
dst:                                             c0 a8
      01 0c
tcp:        00
                      00
data:                    48 54 54 50
checksum:   d0 db
#endif

#include <stdio.h>
#include <stdint.h>

static uint16_t data[] = {
    0x3d87, 0xa97d, /* src ip */
    0xc0a8, 0x010c, /* dst ip */
    0x0006,         /* protocol */
    0x0019,         /* udp length */
    0x0050, 0xd23e, 0xcea7, 0xd733, 0x9fe2, 0x04c6, 0x5018,/* tcp header */
    0x1920, 0x0000, 0x0000,
    0x4854, 0x5450, 0x0000, /* udp data */
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
