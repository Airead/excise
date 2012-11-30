/**
 * @file parse_iptablessave.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/02 10:22:14
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main( void )
{
    FILE   *stream;
    char *p, *q;
    char   buf[1024];
    int chain;                  /*
                                 * 1: prerouting
                                 * 2: input
                                 * 3: forward
                                 * 4: output
                                 * 5: postrouting
                                 */

    memset( buf, '\0', sizeof(buf) );
    stream = popen( "sudo iptables -t mangle -L", "r" );

    chain = 0;
    while (fgets(buf, sizeof(buf), stream) != NULL) {
//        fprintf(stdout, "%s", buf);
        if (strstr(buf, "Chain")) chain++;
        if (chain > 1) break;
        if (strstr(buf, "MARK")) {
            p = strstr(buf, "anywhere");
            if (p) p += strlen("anywhere");
            while (*p == ' ') p++;
            q = p;
            while (*q != ' ') q++;
            *q = '\0';
            fprintf(stdout, "%s\n", p);
        }
    }
    pclose( stream );
    return 0;
}


