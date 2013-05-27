/**
 * @file tree.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/05/08 10:44:20
 */

#ifndef _BINTREE_H_
#define _INTREE_H_

#include <stdbool.h>

#define NODE_MAX 1024

#define CHARBUF_ROWS          20  // def: 20
#define CHARBUF_COLMS          80 // def: 80 (using a huge number, like 500, is a good idea,
#define RECOMMENDED_CONS_WIDTH  80

struct columninfo {
	bool visited;
	int col;
};

struct bintree_node {
	char *key;
	struct bintree_node *l, *r;	/* left, right */
};

int get_keys(char *keys[], char *info);
struct bintree_node *get_bintree(char *info);
void bintree_print_pre_order(struct bintree_node *root);
void bintree_print_in_order(struct bintree_node *root);
void bintree_print_post_order(struct bintree_node *root);
int bintree_height(struct bintree_node *root);
void bintree_print_pretty(struct bintree_node *root);

#endif /* _BINTREE_H_ */
