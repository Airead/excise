/**
 * @file tree.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/05/08 10:43:43
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "bintree.h"

int get_keys(char *keys[], char *info)
{
	int i;
	char *p;
	
	p = info;
	i = 0;
	keys[i++] = p;
	while (info && *info && *info != '\n' && i < NODE_MAX - 1) {
		if (*info == ' ') {
			*info = '\0';
			keys[i++] = info + 1;
		}
		info++;
	}
	if (*info == '\n') {
		*info = '\0';
	}
	keys[i] = NULL;

	return 0;
}

static struct bintree_node *generate_tree(char *keys[], int *num)
{
	struct bintree_node *p;

	if (keys[*num] == NULL) {
		return NULL;
	} else if (*keys[*num] == '/') {
		(*num)++;
		return NULL;
	}

	p = malloc(sizeof(struct bintree_node));
	if (p == NULL) {
		fprintf(stderr, "no memory!\n");
		return NULL;
	}

	p->key = strdup(keys[*num]);
	(*num)++;
	p->l = generate_tree(keys, num);
	p->r = generate_tree(keys, num);

	return p;
}

/*
 *        18	
 *     /      \	
 *    12       10	
 *   /  \    /    \	
 *  7    4  5      6
 *      /    \    /	
 *     8     11  2	
 *                \	
 *                21
 *  18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /
 * 
 * pre order: 18 12 7 4 8 10 5 11 6 2 21 
 * in order: 7 12 8 4 18 5 11 10 2 21 6 
 * post order: 7 8 4 12 11 5 21 2 6 10 18 
 */
struct bintree_node *get_bintree(char *info)
{
	struct bintree_node *root;
	char *keys[NODE_MAX];
	char *tmp_info;
	int i;
	
	if (info == NULL) {
		return NULL;
	}

	tmp_info = strdup(info);
	get_keys(keys, tmp_info);
	
	i = 0;
	root = generate_tree(keys, &i);
	free(tmp_info);

	return root;
}

void bintree_print_pre_order(struct bintree_node *root)
{
	if (root == NULL) {
		return;
	}

	fprintf(stdout, "%s ", root->key);
	bintree_print_pre_order(root->l);
	bintree_print_pre_order(root->r);
}

void bintree_print_in_order(struct bintree_node *root)
{
	if (root == NULL) {
		return;
	}

	bintree_print_in_order(root->l);
	fprintf(stdout, "%s ", root->key);
	bintree_print_in_order(root->r);
}

void bintree_print_post_order(struct bintree_node *root)
{
	if (root == NULL) {
		return;
	}

	bintree_print_post_order(root->l);
	bintree_print_post_order(root->r);
	fprintf(stdout, "%s ", root->key);
}

void bintree_print_in_level_order(struct bintree_node *root)
{
	if (root == NULL) {
		return;
	}
	
	
}

int bintree_height(struct bintree_node *root)
{
	if (root == NULL) {
		return -1;
	}

	int height_left = bintree_height(root->l);
	int height_right = bintree_height(root->r);

	return (height_left > height_right) ? (height_left + 1) : (height_right + 1);
}

void recur_swprintf(char charbuf[][CHARBUF_COLMS], struct bintree_node *root, int width , struct columninfo eachline[], int cur_line, const char *nullstr, int spacesbefore, int spacesafter)
{
	int h;
	float offset;

	h = bintree_height(root);
	offset = width * pow(2, h - cur_line);
	cur_line++;

	if (eachline[cur_line].visited == false) {
		eachline[cur_line].col = (int)(offset / 2);
		eachline[cur_line].visited = true;
	} else {
		eachline[cur_line].col += (int) offset;
		if (eachline[cur_line].col + width > CHARBUF_COLMS) {
			sprintf(charbuf[cur_line], "  BUFFER OVERFLOW DETECTED! ");
		}
	}

	if (root == NULL) {
		sprintf(charbuf[cur_line] + eachline[cur_line].col, "%*.*s", 0, width, nullstr);
		if (cur_line <= h) {
			/* use spaces instead of the nullstr for all the "children" of a NULL node */
			recur_swprintf(charbuf, NULL, width, eachline, cur_line, "          ", spacesbefore, spacesafter);
			recur_swprintf(charbuf, NULL, width, eachline, cur_line, "          ", spacesbefore, spacesafter);
		} else {
			return;
		}
	} else {
		recur_swprintf(charbuf, root->l, width, eachline, cur_line, nullstr, spacesbefore, spacesafter);
		recur_swprintf(charbuf, root->r, width, eachline, cur_line, nullstr, spacesbefore, spacesafter);

		sprintf(charbuf[cur_line] + eachline[cur_line].col - 1, "(%*.*s)", spacesbefore, 1, root->key);
		sprintf(charbuf[cur_line] + eachline[cur_line].col + spacesafter + 2, ")");
	}
}

int omit_cols(char charbuf[][CHARBUF_COLMS], int height) {
	int col;
	int line;
	
	for (col = 0; col < RECOMMENDED_CONS_WIDTH; col++) {
		for (line = 0; line < height + 1; line++) {
			if (charbuf[line][col] != ' ' && charbuf[line][col] != '\0') {
				return col;
			}
		}
	}

	return 0;
}

void bintree_print_pretty(struct bintree_node *root)
{
	if (root == NULL) {
		return;
	}

	int i, j, width = 3, spacesbefore = 2, spacesafter = 1;
	
	char charbuf[CHARBUF_ROWS][CHARBUF_COLMS];
	struct columninfo eachline[CHARBUF_ROWS];

	for (i = 0; i < CHARBUF_ROWS; i++) {
		for (j = 0; j < CHARBUF_COLMS; j++) {
			charbuf[i][j] = ' ';
		}
		eachline[i].visited = false;
		eachline[i].col = 0;
	}
	
	int height = bintree_height(root);
	
	// void recur_swprintf(char charbuf[][CHARBUF_COLMS], struct bintree_node *root, int width , struct columninfo eachline[], int cur_line, const char *nullstr, int spacesbefore, int spacesafter)
	recur_swprintf(charbuf, root, width, eachline, -1, "NULL", spacesbefore, spacesafter);

	j = omit_cols(charbuf, height) - 2;
	j = (j < 0) ? 0 : j;

	for (int row = 0; row <= height + 1; row++) {
		fputc('\n', stdout);
		for (i = j; i < j + RECOMMENDED_CONS_WIDTH && i < CHARBUF_COLMS; i++) {
			fputc(charbuf[row][i], stdout);
		}
		fputc('\n', stdout);
	}
}
