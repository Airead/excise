/**
 * @file bintree_main.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/05/09 11:27:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bintree.h"

#define BUF_SIZE 2048

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	struct bintree_node *bintree;

	fgets(buf, BUF_SIZE, stdin);
	fprintf(stdout, "tree info: %s", buf);

	bintree = get_bintree(buf);

	fprintf(stdout, "pre order: ");
	bintree_print_pre_order(bintree);
	fprintf(stdout, "\n");

	fprintf(stdout, "in order: ");
	bintree_print_in_order(bintree);
	fprintf(stdout, "\n");

	fprintf(stdout, "post order: ");
	bintree_print_post_order(bintree);
	fprintf(stdout, "\n");

	bintree_print_pretty(bintree);

	/* destory bintree */
	return 0;
}
