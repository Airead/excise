/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2012  2月 17 16:21:06 CST
 ********************************************************/

#include <setjmp.h>
#include <stdio.h>

jmp_buf env;
int count = 0;

void f2(void)
{
    printf("f2 begins\n");
    longjmp(env, count++);
    printf("f2 returns\n");
}

void f1(void)
{
    printf("f1 begins\n");
    f2();
    printf("f1 returns\n");
}


int main(void)
{
    int ret;

    ret = setjmp(env);
    if (ret == 0) {
        printf("setjmp returned 0\n");
    } else if (ret < 5) {
        printf("ret is %d\n", ret);
    } else {
        printf("Program terminates: longjmp called\n");
        return 0;
    }

    f1();
    printf("Program terminates normally\n");

    return 0;
}
