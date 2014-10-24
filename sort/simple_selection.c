#include <stdio.h>

typedef enum { TRUE, FALSE } status;

void swap(int *a, int idx1, int idx2)
{
	int tmp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = tmp;
}

void select_sort(int *a, int len)
{
	int i, j, min;

	for (i = 0; i < len - 1; i++) {
		min = i;
		for (j = i + 1; j < len; j++) {
			if (a[min] > a[j])
				min = j;
		}
		if (i != min)
			swap(a, i, min);
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

	select_sort(a, len);
	print_array(a, len);

	return 0;
}
