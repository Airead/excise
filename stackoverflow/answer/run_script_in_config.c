/**
 * @file run_script_in_config.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/16 14:05:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buf[512];
    
    scanf("%s", buf);

    if (!strcmp(buf, "sleep(5)")) {
        printf("sleep...\n");
        sleep(5);
    }

    printf("over\n");

    return 0;
}
