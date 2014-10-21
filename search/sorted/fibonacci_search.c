#include <stdio.h>
#include <stdlib.h>

/* needed : src is sorted */

int get_val(int i, int *a, int n)
{
	if (i >= n)
		i = n - 1;

	return a[i];
}

int fibonacci_search(int *fibo, int *a, int n, const int want)
{
	int low, mid, high, i, k, cnt = 0;

	low = 0, high = n - 1;

	k = 0;
	while (n - 1 > fibo[k] - 1)	/* calc index in array fibonacci */
		k++;

	while (low <= high) {
		cnt++;
		mid = low + fibo[k - 1] - 1;

		if (want < get_val(mid, a, n)) {
			high = mid - 1;
			k = k - 1;
		} else if (want > get_val(mid, a, n)) {
			low = mid + 1;
			k = k - 2;
		} else {
			printf("cnt:%d\n", cnt);
			if (mid <= high)
				return mid;
			else
				return -1;
		}
	}

	return -1;
}

int tail_fibo(int idx, int a, int b)
{
	if (idx < 2)
		return b;
	else
		return tail_fibo(idx - 1, b, a + b);
}

void build_fibo(int **fibo, int num)
{
	int i;

	*fibo = malloc(sizeof(int) * num);
	for (i = 0; i < num; i++) {
		(*fibo)[i] = tail_fibo(i, 1, 1);
	}
}

int main(int argc, char *argv)
{
	const int want = 59;
	int nums, *fibo, src[] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 93 };

	nums = sizeof(src) / sizeof(src[0]);
	build_fibo(&fibo, nums);
	printf("found %d, index %d\n", want,
	       fibonacci_search(fibo, src, nums, want));

	return 0;
}
