/**
 * @file main.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/30 14:27:29
 */

#include "main.h"
#include "do.h"

int main(int argc, char *argv[])
{
    char *act;
    struct person airead;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <action>\n", argv[0]);
        fprintf(stderr, "    action: [learn, done, can, need]\n");
        exit(1);
    }
    act = argv[1];
    
    /* initialize airead */
    strcpy(airead.name, "airead");

    if (strcmp("learn", act) == 0) {
        fprintf(stdout, "learn: \n");
        airead.dowhat = do_learn;
    } else if (strcmp("done", act) == 0) {
        fprintf(stdout, "done: \n");
        airead.dowhat = do_done;
    } else if (strcmp("can", act) == 0) {
        fprintf(stdout, "can: \n");
        airead.dowhat = do_can;
    } else if (strcmp("need", act) == 0) {
        fprintf(stdout, "need: \n");
        airead.dowhat = do_need;
    } else {
        fprintf(stderr, "error! action should be in [learn, done, can, need]\n");
    }    
    return 0;
}

