#include <stdio.h>
#include <stdlib.h>

typedef int queue_ele_type;

typedef struct _queue_node {
	queue_ele_type data;
	struct _queue_node *next;
} queue_node;

typedef struct _link_queue {
	queue_node *front, *rear;
} link_queue;

void init_queue(link_queue * q)
{
	q->front = q->rear = malloc(sizeof(queue_node));
	q->front->next = NULL;	/* init 'next' of node front and rear */
}

void into_queue(link_queue * q, queue_ele_type e)
{
	queue_node *tmp = malloc(sizeof(queue_node));

	tmp->data = e;
	tmp->next = NULL;

	q->rear->next = tmp;
	q->rear = tmp;
}

int out_queue(link_queue * q, queue_ele_type * e)
{
	queue_node *tmp;

	if (q->front == q->rear)
		return -1;

	tmp = q->front->next;
	*e = tmp->data;

	q->front->next = tmp->next;
	if (q->rear == tmp)
		q->rear = q->front;

	free(tmp);
	return 0;
}

int main(int argc, char **argv)
{
	link_queue sans;
	int i, len, tmp, a[] = { 1, 2, 3, 4, 5 };

	len = sizeof(a) / sizeof(a[0]);
	init_queue(&sans);

	for (i = 0; i < len; i++) {
		into_queue(&sans, a[i]);
	}

	for (i = 0; i < len; i++) {
		out_queue(&sans, &tmp);
		printf("%d ", tmp);
	}
	printf("\n");

	return 0;
}
