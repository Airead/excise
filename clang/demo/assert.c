/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2012  2月 17 15:44:15 CST
 ********************************************************/

#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int i;

    i = 5;
    assert(0 <= i && i < 10);
    printf("i = 5 can reach here\n");

    i = 20;
    assert(0 <= i && i < 10);
    printf("i = 20 can reach here\n");

    return 0;
}
