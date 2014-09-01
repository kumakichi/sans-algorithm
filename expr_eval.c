#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 1024
#define CUR_IS_CLOSE_PARENTHESIS 2	/* come across right parenthesis */
#define CUR_IS_LE_THAN_STACK_TOP 1	/* current op char prior is lower or equal than op char on stack top */

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

int num_len(int i)
{
	if (i < 10)
		return 1;
	else
		return 1 + num_len(i / 10);
}

int infix_parser(char *str, int *storage)
{
	char *tmp = str;
	int i, counter = 0;

	while (*tmp) {
		switch (*tmp) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
			storage[counter++] = *tmp;
			tmp += 1;
			break;
		default:
			i = strtol(tmp, NULL, 10);
			tmp += num_len(i);
			storage[counter++] = i;
			break;
		}
	}
	return counter;
}

void print_expr_result(char *prompt, int *result, int len)
{
	int i;

	printf("%s : ", prompt);
	for (i = 0; i < len; i++) {
		switch (result[i]) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
			printf("%c ", result[i]);
			break;
		default:
			printf("%d ", result[i]);
			break;
		}
	}
	printf("\n");
}

int cur_prior_is_le_than_stack_top(char c, link_stack * s)
{
	if (c == ')')
		return CUR_IS_CLOSE_PARENTHESIS;

	if (c == '+' || c == '-')
		if (s->top->data != '(')
			return CUR_IS_LE_THAN_STACK_TOP;

	return 0;
}

void process_op_char(char c, link_stack * s, int *suffix, int *back_cur)
{
	int tmp, flag;

	if (is_empty(s)) {
		push(s, c);
		return;
	}

	flag = cur_prior_is_le_than_stack_top(c, s);
	if (0 != flag) {	/* need pop */
		while (!is_empty(s)) {
			pop(s, &tmp);
			if (flag == CUR_IS_CLOSE_PARENTHESIS && tmp == '(')
				break;
			if (tmp != '(') {
				suffix[*back_cur] = tmp;
				*back_cur += 1;
			}
		}
	}

	if (c != ')') {
		push(s, c);
	}
}

int infix_to_suffix(int *mid, int mid_len, int *suffix)
{
	int i, tmp, counter = 0;
	link_stack sans;

	init_stack(&sans);

	for (i = 0; i < mid_len; i++) {
		switch (mid[i]) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
			process_op_char(mid[i], &sans, suffix, &counter);
			break;
		default:
			suffix[counter++] = mid[i];
			break;
		}
	}

	while (!is_empty(&sans)) {
		pop(&sans, &tmp);
		suffix[counter++] = tmp;
	}

	return counter;
}

int calc_little(int v1, int v2, int op)
{
	switch (op) {
	case '+':
		return v1 + v2;
	case '-':
		return v1 - v2;
	case '*':
		return v1 * v2;
	case '/':
		return v1 / v2;
	}
}

int calc_suffix_expr(int *suffix, int len)
{
	int i, tmp, param1, param2, result = 0;
	link_stack sans;

	init_stack(&sans);

	for (i = 0; i < len; i++) {
		switch (suffix[i]) {
		case '+':
		case '-':
		case '*':
		case '/':
			pop(&sans, &param2);
			pop(&sans, &param1);
			tmp = calc_little(param1, param2, suffix[i]);
			push(&sans, tmp);
			break;
		default:
			push(&sans, suffix[i]);
		}
	}
	pop(&sans, &result);
	return result;
}

int main(int argc, char **argv)
{
	char infix[MAX_BUFF] = { 0 };
	int prefix[MAX_BUFF];	/* storage for infix elements */
	int suffix[MAX_BUFF];	/* suffix representation */

	int infix_cnt, suffix_cnt, result;
	sEleType dat[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	printf("input a expr to eval:\n");
	scanf("%s", infix);
	printf("infix notation : %s\n", infix);

	infix_cnt = infix_parser(infix, prefix);
	print_expr_result("mid representation is", prefix, infix_cnt);

	suffix_cnt = infix_to_suffix(prefix, infix_cnt, suffix);
	print_expr_result("suffix representation is", suffix, suffix_cnt);

	result = calc_suffix_expr(suffix, suffix_cnt);
	printf("eval %s is %d\n", infix, result);

	return 0;
}

/* infix -> suffix : scan string from left to right */
/* 1. if come across num,put it into suffix expr directly */
/* 2. if come across op char(+,-,*,/) X: */
/*    2.1 if X is ')',pop element into suffix expr until come across '(' */
/*    2.2 if priority of X is lower than or equal to priority of op char on the top of the stack,pop all elements on the stack into suffix expr  */
