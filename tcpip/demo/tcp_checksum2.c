/**
 * @file tcp_checksum2.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/17 09:22:17
 */

#if 0
checksum     f0 dc, should be 0xcb5f

0000   20 6a 8a 64 eb 84 00 0c 29 cd 58 d7 08 00 45 00   j.d....).X...E.
0010   01 a8 c0 a2 40 00 2b 06 e5 08 3d 87 a9 69 c0 a8  ....@.+...=..i..
0020   01 0c 00 50 b3 c1 93 26 e9 85 d9 71 7b 32 50 18  ...P...&...q{2P.
0030   19 20 f0 dc 00 00 48 54 54 50 2f 31 2e 30 20 33  . ....HTTP/1.0 3
0040   30 32 20 4d 6f 76 65 64 20 54 65 6d 70 6f 72 61  02 Moved Tempora
0050   72 69 6c 79 0d 0a 53 65 72 76 65 72 3a 20 6e 67  rily..Server: ng
0060   69 6e 78 2f 31 2e 32 2e 30 0d 0a 44 61 74 65 3a  inx/1.2.0..Date:
0070   20 46 72 69 2c 20 30 36 20 4a 75 6c 20 32 30 31   Fri, 06 Jul 201
0080   32 20 30 38 3a 31 34 3a 33 35 20 47 4d 54 0d 0a  2 08:14:35 GMT..
0090   43 6f 6e 74 65 6e 74 2d 54 79 70 65 3a 20 74 65  Content-Type: te
00a0   78 74 2f 68 74 6d 6c 0d 0a 43 6f 6e 74 65 6e 74  xt/html..Content
00b0   2d 4c 65 6e 67 74 68 3a 20 32 31 0d 0a 43 6f 6e  -Length: 21..Con
00c0   6e 65 63 74 69 6f 6e 3a 20 6b 65 65 70 2d 61 6c  nection: keep-al
00d0   69 76 65 0d 0a 4c 6f 63 61 74 69 6f 6e 3a 20 68  ive..Location: h
00e0   74 74 70 3a 2f 2f 77 77 77 2e 31 36 33 2e 63 6f  ttp://www.163.co
00f0   6d 0d 0a 0d 0a 77 65 6c 63 6f 6d 65 20 74 6f 20  m....welcome to 
0100   42 65 69 6a 69 6e 67 0d 0a 0d 0a 00 45 32 32 43  Beijing.....E22C
0110   30 41 33 42 31 42 30 36 41 37 33 35 33 30 31 37  0A3B1B06A7353017
0120   30 30 39 30 36 44 43 41 36 36 34 41 3a 46 47 3d  00906DCA664A:FG=
0130   31 3b 20 65 78 70 69 72 65 73 3d 46 72 69 2c 20  1; expires=Fri, 
0140   31 37 2d 41 75 67 2d 34 32 20 30 31 3a 34 34 3a  17-Aug-42 01:44:
0150   32 32 20 47 4d 54 3b 20 70 61 74 68 3d 2f 3b 20  22 GMT; path=/; 
0160   64 6f 6d 61 69 6e 3d 2e 62 61 69 64 75 2e 63 6f  domain=.baidu.co
0170   6d 0d 0a 50 33 50 3a 20 43 50 3d 22 20 4f 54 49  m..P3P: CP=" OTI
0180   20 44 53 50 20 43 4f 52 20 49 56 41 20 4f 55 52   DSP COR IVA OUR
0190   20 49 4e 44 20 43 4f 4d 20 22 0d 0a 43 6f 6e 6e   IND COM "..Conn
01a0   65 63 74 69 6f 6e 3a 20 4b 65 65 70 2d 41 6c 69  ection: Keep-Ali
01b0   76 65 0d 0a 0d 0a                                ve....
#endif

#include <stdio.h>
#include <stdint.h>

static uint16_t data[] = {
    0x3d87, 0xa97d, /* src ip */
    0xc0a8, 0x010c, /* dst ip */
    0x0194,         /* udp length */
    0x0006,         /* protocol */
    0x0050, 0xb3c1, 0x9326, 0xe985, 0xd971, 0x7b32,
    0x5018, 0x1920, 0x0000, 0x0000, 0x4854, 0x5450,
    0x2f31, 0x2e30, 0x2033, 0x3032, 0x204d, 0x6f76,
    0x6564, 0x2054, 0x656d, 0x706f, 0x7261, 0x7269,
    0x6c79, 0x0d0a, 0x5365, 0x7276, 0x6572, 0x3a20,
    0x6e67, 0x696e, 0x782f, 0x312e, 0x322e, 0x300d,
    0x0a44, 0x6174, 0x653a, 0x2046, 0x7269, 0x2c20,
    0x3036, 0x204a, 0x756c, 0x2032, 0x3031, 0x3220,
    0x3038, 0x3a31, 0x343a, 0x3335, 0x2047, 0x4d54,
    0x0d0a, 0x436f, 0x6e74, 0x656e, 0x742d, 0x5479,
    0x7065, 0x3a20, 0x7465, 0x7874, 0x2f68, 0x746d,
    0x6c0d, 0x0a43, 0x6f6e, 0x7465, 0x6e74, 0x2d4c,
    0x656e, 0x6774, 0x683a, 0x2032, 0x310d, 0x0a43,
    0x6f6e, 0x6e65, 0x6374, 0x696f, 0x6e3a, 0x206b,
    0x6565, 0x702d, 0x616c, 0x6976, 0x650d, 0x0a4c,
    0x6f63, 0x6174, 0x696f, 0x6e3a, 0x2068, 0x7474,
    0x703a, 0x2f2f, 0x7777, 0x772e, 0x3136, 0x332e,
    0x636f, 0x6d0d, 0x0a0d, 0x0a77, 0x656c, 0x636f,
    0x6d65, 0x2074, 0x6f20, 0x4265, 0x696a, 0x696e,
    0x670d, 0x0a0d, 0x0a00, 0x4532, 0x3243, 0x3041,
    0x3342, 0x3142, 0x3036, 0x4137, 0x3335, 0x3330,
    0x3137, 0x3030, 0x3930, 0x3644, 0x4341, 0x3636,
    0x3441, 0x3a46, 0x473d, 0x313b, 0x2065, 0x7870,
    0x6972, 0x6573, 0x3d46, 0x7269, 0x2c20, 0x3137,
    0x2d41, 0x7567, 0x2d34, 0x3220, 0x3031, 0x3a34,
    0x343a, 0x3232, 0x2047, 0x4d54, 0x3b20, 0x7061,
    0x7468, 0x3d2f, 0x3b20, 0x646f, 0x6d61, 0x696e,
    0x3d2e, 0x6261, 0x6964, 0x752e, 0x636f, 0x6d0d,
    0x0a50, 0x3350, 0x3a20, 0x4350, 0x3d22, 0x204f,
    0x5449, 0x2044, 0x5350, 0x2043, 0x4f52, 0x2049,
    0x5641, 0x204f, 0x5552, 0x2049, 0x4e44, 0x2043,
    0x4f4d, 0x2022, 0x0d0a, 0x436f, 0x6e6e, 0x6563,
    0x7469, 0x6f6e, 0x3a20, 0x4b65, 0x6570, 0x2d41,
    0x6c69, 0x7665, 0x0d0a, 0x0d0a,
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
