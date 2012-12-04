/**
 * @file main.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/30 14:27:29
 */

#include "main.h"
#include "do.h"
#include "lib.h"

static void analyze_person(struct person p, char *act)
{
    printf("name: %s\n", p.name);
    printf("  %s: \n", act);
    p.dowhat();
}

int main(int argc, char *argv[])
{
    char *act;
    struct person airead;

    if (argc < 2) { 
        fprintf(stderr, "usage: %s <action>\n", argv[0]);
        fprintf(stderr, "    action: [study, done, can, need]\n");
        exit(1);
    }
    act = argv[1];
    
    /* initialize airead */
    strcpy(airead.name, "airead");

    if (strcmp("study", act) == 0) {
        fprintf(stdout, "study: \n");
        airead.dowhat = do_studied;
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
	exit(1);
    }

    analyze_person(airead, act);

    return 0;
}

