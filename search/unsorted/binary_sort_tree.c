#include <stdio.h>
#include <stdlib.h>

typedef enum { TRUE, FALSE } status;

typedef struct _binode {
	int data;
	struct _binode *lchild;
	struct _binode *rchild;
} binode, *bitree;

/* check whether key exists in tree 't' */
/* f, parent node */
/* if found, p point to the node and return TRUE */
/* if not found, p point to the last node in this search,and return FALSE */

status search_bst(bitree t, int key, bitree f, bitree * p)
{
	if (NULL == t) {
		*p = f;
		return FALSE;
	} else if (key == t->data) {
		*p = t;
		return TRUE;
	} else if (key < t->data)
		return search_bst(t->lchild, key, t, p);
	else
		return search_bst(t->rchild, key, t, p);
}

status insert_bst(bitree * t, int key)
{
	bitree p, tmp;

	if (TRUE == search_bst(*t, key, NULL, &p))
		return FALSE;	/* node already existed */

	tmp = malloc(sizeof(binode));
	tmp->data = key;
	tmp->lchild = tmp->rchild = NULL;

	if (NULL == p)
		*t = tmp;	/* root */
	else if (key < p->data)
		p->lchild = tmp;
	else
		p->rchild = tmp;

	return TRUE;
}

status real_delete(bitree * p)
{
	bitree q, s;

	if (NULL == (*p)->rchild) {
		q = *p;
		*p = (*p)->lchild;
		free(q);
	} else if (NULL == (*p)->lchild) {
		q = *p;
		*p = (*p)->rchild;
		free(q);
	} else {		/* see bst.png */
		q = *p;
		s = (*p)->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;	/* 'q' is parent of 's' */
		}

		(*p)->data = s->data;

		if (q != *p)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}

	return TRUE;
}

status delete_bst(bitree * t, int key)
{
	bitree p;

	if (FALSE == search_bst(*t, key, NULL, &p))
		return FALSE;	/* node not found */

	real_delete(&p);
}

void preOrderTraverse(bitree t)
{
	if (NULL == t)
		return;
	printf("%d\n", t->data);
	preOrderTraverse(t->lchild);
	preOrderTraverse(t->rchild);
}

int main(int argc, char *argv[])
{
	int i, n;
	bitree t = NULL;
	int a[] = { 62, 88, 58, 47, 35, 73, 51, 95, 99, 37, 93 };

	n = sizeof(a) / sizeof(a[0]);
	for (i = 0; i < n; i++) {
		insert_bst(&t, a[i]);
	}

	preOrderTraverse(t);
	delete_bst(&t, 47);
	printf("after delete 47:\n");
	preOrderTraverse(t);

	return 0;
}
