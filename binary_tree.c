#include <stdio.h>
#include <stdlib.h>

typedef struct binode_ {
	int data;
	struct binode_ *l;
	struct binode_ *r;
} binode;

	    /*      1 */
	    /*   2     3 */
	    /* 4   5 6   7 */
void preOrderTraverse(binode * tree)
{
	if (NULL == tree)
		return;
	printf("%d\n", tree->data);
	preOrderTraverse(tree->l);
	preOrderTraverse(tree->r);
}

void midOrderTraverse(binode * tree)
{
	if (NULL == tree)
		return;
	midOrderTraverse(tree->l);
	printf("%d\n", tree->data);
	midOrderTraverse(tree->r);
}

void postOrderTraverse(binode * tree)
{
	if (NULL == tree)
		return;
	postOrderTraverse(tree->l);
	postOrderTraverse(tree->r);
	printf("%d\n", tree->data);
}

void create_node(binode ** tree, int val)
{
	*tree = malloc(sizeof(binode));
	(*tree)->data = val;
}

int main(void)
{
	binode *tree;

	create_node(&tree, 1);

	create_node(&(tree->l), 2);
	create_node(&(tree->r), 3);

	create_node(&(tree->l->l), 4);
	create_node(&(tree->l->r), 5);

	create_node(&(tree->r->l), 6);
	create_node(&(tree->r->r), 7);

	printf("[preOrderTraverse]\n");
	preOrderTraverse(tree);
	printf("[midOrderTraverse]\n");
	midOrderTraverse(tree);
	printf("[postOrderTraverse]\n");
	postOrderTraverse(tree);
}
