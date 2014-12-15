#include <stdio.h>
#include <stdlib.h>

typedef struct binode_ {
	int data;
	int ltag;
	int rtag;
	struct binode_ *l;
	struct binode_ *r;
} binode;

enum { CHILD = 0, THREAD };

	    /*      1 */
	    /*   2     3 */
	    /* 4   5 6   7 */

void InThreading(binode * node)
{
	static binode *prev = NULL;

	if (NULL == node)
		return;

	InThreading(node->l);

	if (!node->l) {
		node->l = prev;
		node->ltag = THREAD;
	}

	if (prev && !prev->r) {
		prev->r = node;
		prev->rtag = THREAD;
	}
	prev = node;

	InThreading(node->r);
}

void create_node(binode ** tree, int val)
{
	*tree = malloc(sizeof(binode));
	(*tree)->data = val;
}

void InTraverse(binode * tree)
{
	binode *p = tree;

	for (;;) {
		while (p->ltag == CHILD)	/* move to the left most node */
			p = p->l;

		printf("%d\n", p->data);

		while (p->rtag == THREAD) {
			p = p->r;
			printf("%d\n", p->data);
		}
		p = p->r;

		if (NULL == p)
			break;
	}
}

binode *create_tree()
{
	binode *tree;

	create_node(&tree, 1);

	create_node(&(tree->l), 2);
	create_node(&(tree->r), 3);

	create_node(&(tree->l->l), 4);
	create_node(&(tree->l->r), 5);

	create_node(&(tree->r->l), 6);
	create_node(&(tree->r->r), 7);

	return tree;
}

int main(void)
{
	binode *tree = create_tree();

	InThreading(tree);
	printf("In Sequence:\n");
	InTraverse(tree);

	return 0;
}
