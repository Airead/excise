/**
 * @file inet_pton.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/18 15:23:35
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int ret;
    char bufip[INET_ADDRSTRLEN];
    int32_t ip;
    char *ipstr;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <ip_addr> \n", argv[0]);
        exit(1);
    }

    ipstr = strdup(argv[1]);
    ret = inet_pton(PF_INET, ipstr, &ip);
    free(ipstr);

    fprintf(stdout, "pton ret: %d\n", ret);

    inet_ntop(PF_INET, &ip, bufip, INET_ADDRSTRLEN);
    fprintf(stdout, "ip: %s\n", bufip);
    
    return 0;
}


