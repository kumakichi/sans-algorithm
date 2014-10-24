#include <stdio.h>

typedef enum { TRUE, FALSE } status;

void swap(int *a, int idx1, int idx2)
{
	int tmp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = tmp;
}

void bubble_sort_v1(int *a, int len, int *count)
{
	int i, j;

	for (i = len - 2, *count = 0; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			(*count)++;
			if (a[j] > a[j + 1])
				swap(a, j, j + 1);
		}
	}
}

void bubble_sort_v2(int *a, int len, int *count)
{
	int i, j;
	status flag = TRUE;

	for (i = len - 2, *count = 0; i >= 0 && TRUE == flag; i--) {
		flag = FALSE;
		for (j = 0; j <= i; j++) {
			(*count)++;
			if (a[j] > a[j + 1]) {
				swap(a, j, j + 1);
				flag = TRUE;	/* if no swap any more, everything is ok */
			}
		}
	}
}

void print_array(int *a, int len, int count)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\ncost %d\n", count);
}

int main(int argc, char *argv[])
{
	int len, cnt;
	int a[] = { 2, 1, 3, 5, 4, 6, 7, 8, 9 };
	int b[] = { 2, 1, 3, 5, 4, 6, 7, 8, 9 };

	len = sizeof(a) / sizeof(a[0]);

	bubble_sort_v1(a, len, &cnt);
	print_array(a, len, cnt);

	bubble_sort_v2(b, len, &cnt);
	print_array(b, len, cnt);

	return 0;
}
