/**
 * @file answer_first_2_digits.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/16 14:22:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* usage: after runing, input 2056 12 31 */
int main(int argc, char *argv[])
{
    char num_str[3][16];
    char tmp[16];
    int i;

    for (i = 0; i < 3; i++) {
        scanf("%s", num_str[i]);
    }

    printf("year: %s\n", num_str[0]);
    printf("month: %s\n", num_str[1]);
    printf("day :%s\n", num_str[2]);

    strcpy(tmp, num_str[0]);
    tmp[2] = '\0';

    printf("first 2 digits: %s\n", tmp);
    
    return 0;
}

