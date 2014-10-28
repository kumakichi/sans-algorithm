#include <stdio.h>

void swap(int *a, int idx1, int idx2)
{
	int tmp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = tmp;
}

void heap_adjust(int *a, int s, int e)
{
	int tmp, i;

	tmp = a[s];
	for (i = 2 * s; i <= e; i *= 2) {
		if (i < e && a[i] < a[i + 1])
			++i;	/* i is the idx of the child whose val is bigger */
		if (tmp >= a[i])	/* if parent is bigger than the child(the bigger one) */
			break;
		a[s] = a[i];	/* parent is lower than child, copy child val to parent() */
		s = i;		/* point to the new ... */
	}
	a[s] = tmp;
}

void heap_sort(int *a, int len)
{
	int i;
	for (i = len / 2; i >= 0; i--)
		heap_adjust(a, i, len);

	for (i = len; i >= 1; i--) {
		swap(a, 0, i);
		heap_adjust(a, 0, i - 1);
	}
}

void print_array(int *a, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{
	int len, cnt;
	int a[] = { 2, 1, 3, 5, 4, 6, 7, 8, 9 };

	len = sizeof(a) / sizeof(a[0]);

	heap_sort(a, len - 1);
	print_array(a, len);

	return 0;
}
