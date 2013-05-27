/**
 * @file test_bintree.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/05/08 13:51:09
 */

#include "lcut.h"
#include "bintree.h"
#include <string.h>

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
 */
static void tc_get_keys(lcut_tc_t *tc, void *data)
{
	char *keys[NODE_MAX];
	char info[] = "18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /";
	char *result = "18|12|7|/|/|4|8|/|/|/|10|5|/|11|/|/|6|2|/|21|/|/|/|";
	char buf[NODE_MAX * 4];
	int i;

	get_keys(keys, info);
	
	memset(buf, 0, sizeof(buf));
	i = 0;
	while (keys[i]) {
		strcat(buf, keys[i]);
		strcat(buf, "|");
		i++;
	}
	
	LCUT_STR_EQUAL(tc, result, buf);
}

static void tc_get_bintree(lcut_tc_t *tc, void *data)
{
	char *info = "18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /";
	struct bintree_node *root, *l1, *l2, *l3, *l4;
	
	root = get_bintree(info);
	LCUT_STR_EQUAL(tc, "18", root->key);
	l1 = root->l;
	LCUT_STR_EQUAL(tc, "12", l1->key);
	l2 = l1->l;
	LCUT_STR_EQUAL(tc, "7", l2->key);
	LCUT_PTR_EQUAL(tc, NULL, l2->l);
	LCUT_PTR_EQUAL(tc, NULL, l2->r);
	l2 = l1->r;
	LCUT_STR_EQUAL(tc, "4", l2->key);
	LCUT_PTR_EQUAL(tc, NULL, l2->r);
	l3 = l2->l;
	LCUT_STR_EQUAL(tc, "8", l3->key);
	LCUT_PTR_EQUAL(tc, NULL, l3->l);
	LCUT_PTR_EQUAL(tc, NULL, l3->r);
	l1 = root->r;
	LCUT_STR_EQUAL(tc, "10", l1->key);
	l2 = l1->l;
	LCUT_STR_EQUAL(tc, "5", l2->key);
	LCUT_PTR_EQUAL(tc, NULL, l2->l);
	l3 = l2->r;
	LCUT_STR_EQUAL(tc, "11", l3->key);
	LCUT_PTR_EQUAL(tc, NULL, l3->l);
	LCUT_PTR_EQUAL(tc, NULL, l3->r);
	l2 = l1->r;
	LCUT_STR_EQUAL(tc, "6", l2->key);
	LCUT_PTR_EQUAL(tc, NULL, l3->r);
	l3 = l2->l;
	LCUT_STR_EQUAL(tc, "2", l3->key);
	LCUT_PTR_EQUAL(tc, NULL, l3->l);
	l4 = l3->r;
	LCUT_STR_EQUAL(tc, "21", l4->key);
	LCUT_PTR_EQUAL(tc, NULL, l4->l);
	LCUT_PTR_EQUAL(tc, NULL, l4->r);
}

static void tc_bintree_print_in_order(lcut_tc_t *tc, void *data)
{
	char *info = "18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /";
	struct bintree_node *root;

	root = get_bintree(info);
	fprintf(stdout, "pre order: ");
	bintree_print_pre_order(root);
	fprintf(stdout, "\n");

	fprintf(stdout, "in order: ");
	bintree_print_in_order(root);
	fprintf(stdout, "\n");

	fprintf(stdout, "post order: ");
	bintree_print_post_order(root);
	fprintf(stdout, "\n");
	/* TODO: destroy tree */
}

static void tc_bintree_height(lcut_tc_t *tc, void *data)
{
	struct treeinfos {
		char *info;
		int height;
	};
	int i;
	struct bintree_node *root;
	struct treeinfos ts[] = {
/*
 *        18	                 4
 *     /      \	    
 *    12       10                3	
 *   /  \    /    \	
 *  7    4  5      6             2 
 *      /    \    /	
 *     8     11  2	         1
 *                \	
 *                21             0
 *  18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /
 */
		{"18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / 21 / / /", 4},
/*
 *        18	
 *     /      \	
 *    12       10	
 *   /  \    /    \	
 *  7    4  5      6
 *      /    \    /	
 *     8     11  2
 *
 *  18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / / /
 */
		{"18 12 7 / / 4 8 / / / 10 5 / 11 / / 6 2 / / /", 3},
/*
 *        18	
 *     /      \	
 *    12       10	
 *   /
 *  7
 *   
 *   
 *
 *  18 12 7 / / / 10 / /
 */
		{"18 12 7 / / / 10 / /", 2},
/*
 *        18	
 *     /      \	
 *    12       10	
 *   /  \
 *  7    4
 *      /
 *     8
 *
 *  18 12 7 / / 4 8 / / / 10 / /
 */
		{"18 12 7 / / 4 8 / / / 10 / /", 3},
/*
 *        18	
 *     /      \	
 *    12       10	
 *
 *  18 12 / / 10 / /
 */
		{"18 12 / / 10 / /", 1}
	};

	for (i = 0; i < sizeof(ts) / sizeof(ts[0]); i++) {
		int h;
		root = get_bintree(ts[i].info);
		h = bintree_height(root);
		/* TODO: destroy tree */
		LCUT_INT_EQUAL(tc, ts[i].height, h);
	}
}

int main(int argc, char *argv[])
{
	lcut_ts_t *suite = NULL;
	
	LCUT_TEST_BEGIN("bintree test", NULL, NULL);

	LCUT_TS_INIT(suite, "bintree test suite", NULL, NULL);

	LCUT_TC_ADD(suite, "get_keys() test case", tc_get_keys, NULL, NULL, NULL);
	LCUT_TC_ADD(suite, "get_bintree() test case", tc_get_bintree, NULL, NULL, NULL);
	LCUT_TC_ADD(suite, "print_bintree_in_order() test case", tc_bintree_print_in_order, NULL, NULL, NULL);
	LCUT_TC_ADD(suite, "bintree_height() test case", tc_bintree_height, NULL, NULL, NULL);

	LCUT_TS_ADD(suite);

	LCUT_TEST_RUN();
	LCUT_TEST_REPORT();
	LCUT_TEST_END();

	LCUT_TEST_RESULT();

	return 0;
}
