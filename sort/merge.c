#include <stdio.h>
#include <stdlib.h>

void merge(int src[], int result[], int s, int m, int e)
{				/* start,middle,end */
	int i, j, k;

	k = i = s;
	j = m + 1;

	while (i <= m && j <= e) {
		if (src[i] < src[j])
			result[k++] = src[i++];
		else
			result[k++] = src[j++];
	}

	while (i <= m)
		result[k++] = src[i++];

	while (j <= e)
		result[k++] = src[j++];
}

void merge_sort(int src[], int result[], int s, int e)
{
	int m;
	int tmp[10];

	if (s == e) {
		result[s] = src[s];
	} else {
		m = (s + e) / 2;	/* middle */
		merge_sort(src, tmp, s, m);
		merge_sort(src, tmp, m + 1, e);
		merge(tmp, result, s, m, e);
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
	int *b;

	len = sizeof(a) / sizeof(a[0]);
	b = malloc(sizeof(int) * len);

	merge_sort(a, b, 0, len - 1);
	print_array(b, len);

	free(b);
	return 0;
}
