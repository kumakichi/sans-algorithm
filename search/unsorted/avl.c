#include <stdio.h>
#include <stdlib.h>

#define LH +1			/* left */
#define EH 0			/* equal */
#define RH -1			/* right */

typedef enum { TRUE, FALSE } status;
/* typedef enum { FALSE,TRUE } status; */

typedef struct _binode {
	int data;
	int bf;			/* balance factor */
	struct _binode *lchild, *rchild;
} binode, *bitree;

	/*      9            7 */
	/*    /   \         / \ */
	/*   7     10      6   9 */
	/*  / \              /   \ */
	/* 6   8            8    10 */
/* 右旋:左子7升主;9降子,且为右子;故原子7右子(8)须移 */
void r_rotate(bitree * t)
{
	bitree l;
	l = (*t)->lchild;
	(*t)->lchild = l->rchild;
	l->rchild = *t;
	*t = l;
}

     /*   7                  9      */
     /*  / \               /   \    */
     /* 6   9             7     10  */
     /*   /   \          / \        */
     /*  8    10        6   8       */
/* 左旋:右子9升主;7降为子，左子;7损右子，9需添左子 */
void l_rotate(bitree * t)
{
	bitree r;
	r = (*t)->rchild;
	(*t)->rchild = r->lchild;
	r->lchild = *t;
	*t = r;
}

void left_too_high(bitree * t)
{
	bitree l, lr;
	l = (*t)->lchild;
	switch (l->bf) {
	case LH:
		(*t)->bf = l->bf = EH;
		r_rotate(t);
		break;
	case RH:
		lr = l->rchild;
		switch (lr->bf) {
		case LH:
			(*t)->bf = RH;
			l->bf = EH;
			break;
		case EH:
			(*t)->bf = l->bf = EH;
			break;
		case RH:
			(*t)->bf = EH;
			l->bf = LH;
			break;
		}
		lr->bf = EH;
		l_rotate(&(*t)->lchild);
		r_rotate(t);
	}
}

void right_too_high(bitree * t)
{
	bitree r, rl;
	r = (*t)->rchild;
	switch (r->bf) {
	case RH:
		(*t)->bf = r->bf = EH;
		l_rotate(t);
		break;
	case LH:
		rl = r->lchild;
		switch (rl->bf) {
		case RH:
			(*t)->bf = LH;
			r->bf = EH;
			break;
		case EH:
			(*t)->bf = r->bf = EH;
			break;
		case LH:
			(*t)->bf = EH;
			r->bf = RH;
			break;
		}
		rl->bf = EH;
		r_rotate(&(*t)->rchild);
		l_rotate(t);
	}
}

void insert_left_succeed(bitree * t, status * taller)
{
	switch ((*t)->bf) {
	case LH:		/* left succeed, and left already higher */
		left_too_high(t);
		*taller = FALSE;
		break;
	case EH:
		(*t)->bf = LH;
		*taller = TRUE;
		break;
	case RH:
		(*t)->bf = EH;
		*taller = FALSE;
		break;
	}
}

void insert_right_succeed(bitree * t, status * taller)
{
	switch ((*t)->bf) {
	case LH:
		(*t)->bf = EH;
		*taller = FALSE;
		break;
	case EH:
		(*t)->bf = RH;
		*taller = TRUE;
		break;
	case RH:
		right_too_high(t);
		*taller = FALSE;
		break;
	}
}

status insert_avl(bitree * t, int e, status * taller)
{
	if (NULL == *t) {	/* new node inserted */
		*t = malloc(sizeof(binode));
		(*t)->data = e;
		(*t)->lchild = (*t)->rchild = NULL;
		(*t)->bf = EH;
		*taller = TRUE;
	} else {
		if (e == (*t)->data) {
			*taller = FALSE;
			return FALSE;
		}

		if (e < (*t)->data) {	/* try left */
			if (FALSE == insert_avl(&(*t)->lchild, e, taller))
				return FALSE;
			if (TRUE == *taller)
				insert_left_succeed(t, taller);
		} else {	/* try right */
			if (FALSE == insert_avl(&(*t)->rchild, e, taller))
				return FALSE;
			if (TRUE == *taller)
				insert_right_succeed(t, taller);
		}
	}
	return TRUE;
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
	int i, size;
	bitree t = NULL;
	status taller;
	int a[] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };

	size = sizeof(a) / sizeof(a[0]);
	for (i = 0; i < size; i++)
		insert_avl(&t, a[i], &taller);

	preOrderTraverse(t);

	return 0;
}
