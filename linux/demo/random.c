/**
 * @file random.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/23 11:29:44
 */

#include <stdio.h>
#include <stdlib.h>

#if 0
int rand(void);
int rand_r(unsigned int *seedp);
void srand(unsigned int seed);
#endif

int main(int argc, char *argv[])
{
    int i;

    srand(47);

    for (i = 0; i < 100; i++) {
        fprintf(stdout, "%d\n", rand());
    }

    return 0;
}
