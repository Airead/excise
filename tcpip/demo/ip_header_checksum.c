/**
 * @file ip_header_checksum.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/06/25 16:16:37
 */

#include <stdio.h>
#include <stdint.h>

uint32_t ip_header_with_checksum[10] = {
    0x4500, 0x0028, 0x0000, 0x4000, 0x4006, 
    0xb307, 0xac10, 0x000c, 0x790e, 0x629e
};

uint32_t ip_header_without_checksum[10] = {
    0x4500, 0x0028, 0x0000, 0x4000, 0x4006, 
    0x0000, 0xac10, 0x000c, 0x790e, 0x629e
};

int main(int argc, char *argv[])
{
    int i;

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

    return 0;
}


