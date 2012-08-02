/**
 * @file ip_header_checksum.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/06/25 16:16:37
 */

#include <stdio.h>
#include <stdint.h>

uint16_t ip_header_with_checksum[10] = {
    0x4500, 0x0028, 0x0000, 0x4000, 0x4006, 
    0xb307, 0xac10, 0x000c, 0x790e, 0x629e
};

uint16_t ip_header_without_checksum[10] = {
    0x4500, 0x0028, 0x0000, 0x4000, 0x4006, 
    0x0000, 0xac10, 0x000c, 0x790e, 0x629e
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
    int i;
    unsigned short check;

    printf("ip_header_without_checksum:\n");
    for (i = 0; i < 10; i++) {
        printf("%04x ", ip_header_without_checksum[i]);
    }
    printf("\n");

    printf("ip_header_with_checksum:\n");
    for (i = 0; i < 10; i++) {
        printf("%04x ", ip_header_with_checksum[i]);
    }
    printf("\n");

    check = checksum((unsigned short *)ip_header_without_checksum, 10);
    printf("check = %04x\n", (unsigned short)check);

    return 0;
}
