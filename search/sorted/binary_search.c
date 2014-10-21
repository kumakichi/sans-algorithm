#include <stdio.h>

/* needed : src is sorted */

int binary_search(int *src, int nums, const int want)
{
	int low, mid, high, cnt = 0;

	low = 0, high = nums - 1;

	while (low <= high) {
		cnt++;
		mid = (low + high) / 2;
		if (src[mid] > want)
			high = mid - 1;
		else if (src[mid] < want)
			low = mid + 1;
		else {
			printf("cnt:%d\n", cnt);
			return mid;
		}
	}

	return -1;
}

int main(int argc, char *argv)
{
	const int want = 59;
	int nums, src[] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 93 };

	nums = sizeof(src) / sizeof(src[0]);
	printf("found %d, index %d\n", want, binary_search(src, nums, want));

	return 0;
}
