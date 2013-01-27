/**
 * @file getopt_long.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/25 11:11:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int a;
static int b;
static int c;

static int get_options(int argc, char *argv[])
{
    int ret;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"longa", required_argument, 0, 'a'},
            {"longb", no_argument, 0, 'b'},
            {"longc", no_argument, 0, 'c'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0 }
        };

        ret = getopt_long(argc, argv, "a:bch",
                        long_options, &option_index);
        if (ret == -1)
            break;

        switch (ret) {
        case 'a':
            a = strtol(optarg, NULL, 10);
            break;
        case 'b':
            b = 1;
            break;
        case 'h':
            goto help;
            break;
        case 'c':
            c = 2;
        case '?':
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        fprintf(stderr, "can not get options correct\n");
        return -1;
    }

    return 0;
help:
    return -1;                  /* return -1 will call help_print() in main() */
}

static void help_print(void)
{
    fprintf(stderr, 
            "usage: getopt_long [--longa=num] [--longb] [--longc] [--help]\n"
            "\n"
            "  -a, --longa=level_num,\n"
            "  -b, --longb,   b = 1\n"
            "  -c, --longc, c = 2\n"
            "  -h, --help,          print help\n"     
            "\n");
}

int main(int argc, char *argv[])
{
    
    if (get_options(argc, argv) < 0) {
        help_print();
        exit(1);
    }

    fprintf(stdout, "a %d, b %d, c %d\n", a, b, c);

    return 0;
}
