/**
 * @file tcp_checksum2.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/17 09:22:17
 */


#if 0
checksum c89d

0000   00 0c 29 cd 58 d7 20 6a 8a 64 eb 84 08 00 45 00  ..).X. j.d....E.
0010   00 28 00 00 40 00 40 06 92 2b c0 a8 01 0c 3d 87  .(..@.@..+....=.
0020   a9 69 e7 59 00 50 aa b6 4c 8f 5c 11 7c 90 50 10  .i.Y.P..L.\.|.P.
0030   87 00 c8 9d 00 00                                ......

src ip                               c0 a8 01 0c
dst ip                                           3d 87
       a9 69
tcp len                           
#endif

#include <stdio.h>
#include <stdint.h>
                                                          
static uint16_t data[] = {
0xc8e9,
0x5000,
0x430a,
0xd7bd,
0x756e,
0xe728,
0x1050,
0x0087,
0x0000,
0x0000,
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
