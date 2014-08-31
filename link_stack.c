#include <stdio.h>
#include <stdlib.h>

typedef int sEleType;

typedef struct _stack_node {
	sEleType data;
	struct _stack_node *next;
} stack_node, *p_stack_node;

typedef struct _link_stack {
	p_stack_node top;
	int count;
} link_stack;

void init_stack(link_stack * s)
{
	s->top = NULL;
	s->count = 0;
}

void push(link_stack * s, sEleType e)
{
	p_stack_node tmp = malloc(sizeof(stack_node));
	tmp->next = s->top;
	tmp->data = e;
	s->top = tmp;
	s->count++;
}

int is_empty(link_stack * s)
{
	if (s->count == 0)
		return 1;
	else
		return 0;
}

int pop(link_stack * s, sEleType * e)
{
	p_stack_node tmp;

	if (is_empty(s))
		return -1;

	*e = s->top->data;
	tmp = s->top;
	s->top = tmp->next;
	free(tmp);
	s->count--;

	return 0;
}

int main(int argc, char **argv)
{
	link_stack sans;
	int i, len;
	sEleType dat[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	init_stack(&sans);

	len = sizeof(dat) / sizeof(dat[0]);
	for (i = 0; i < len; i++) {
		push(&sans, dat[i]);
	}

	while (!is_empty(&sans)) {
		pop(&sans, &i);
		printf("%d ", i);
	}
	printf("\n");

	return 0;
}
