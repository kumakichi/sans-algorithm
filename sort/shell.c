#include <stdio.h>

/* shell sort is kind of insertion sort */

void shell_sort(int *a, int len)
{
	int i, j, bak;
	int inc = len;

	do {
		inc = inc / 3;
		for (i = inc; i < len; i++) {
			if (a[i] < a[i - inc]) {
				bak = a[i];
				for (j = i - inc; j >= 0 && a[j] > bak; j -= inc)
					a[j + inc] = a[j];
				a[j + inc] = bak;
			}
		}
	} while (inc > 1);
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

	shell_sort(a, len);
	print_array(a, len);

	return 0;
}
