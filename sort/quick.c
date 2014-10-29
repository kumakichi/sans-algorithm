#include <stdio.h>
#include <stdlib.h>

int partition(int *a, int low, int high)
{
	int pivotkey;

	pivotkey = a[low];
	while (low < high) {
		while (low < high && a[high] >= pivotkey)
			high--;
		a[low] = a[high];	/* swap(a, low, high);move val in 'high' to 'low',  point to 'high',next step scan from 'low' */
		while (low < high && a[low] <= pivotkey)
			low++;
		a[high] = a[low];	/* swap(a, low, high);found val bigger than pivot,move val in 'low' to 'high', point to 'low', next step,scan from 'high'  */
	}
	a[low] = pivotkey;	/* a[low] = pivotkey is the same */

	return low;
}

void quick_sort(int *a, int low, int high)
{
	int pivot;

	if (low < high) {
		pivot = partition(a, low, high);
		quick_sort(a, low, pivot - 1);	/* values lower than pivotkey */
		quick_sort(a, pivot + 1, high);	/* values higher than pivotkey */
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

	quick_sort(a, 0, len - 1);
	print_array(a, len);

	return 0;
}
