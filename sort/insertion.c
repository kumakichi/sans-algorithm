#include <stdio.h>

void insert_sort(int *a, int len)
{
	int i, j, bak;

	for (i = 1; i < len; i++) {
		if (a[i] < a[i - 1]) {
			bak = a[i];	/* insert a[i] into sorted list(a[0] to a[i-1]) */
			for (j = i - 1; a[j] > bak && j >= 0; j--)
				a[j + 1] = a[j];	/* move forward */
			a[j + 1] = bak;	/* last j-- */
		}
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

	insert_sort(a, len);
	print_array(a, len);

	return 0;
}
