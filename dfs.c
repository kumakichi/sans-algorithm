#include <stdio.h>

/* goal : select some numbers from the array,let the sum of the numbers equals want */

#define ELEMENT_NUM 4
#define WANT		7

/*       start       */
/*     /       \ +1  */
/*    o         o    */
/*   / \+2     / \+2 */
/*  o    o    o   o  */
/* /\+4  /\+4  ...   */

int a[ELEMENT_NUM] = { 1, 2, 4, 7 };
int b[ELEMENT_NUM] = { 0 };

int loop_cnt = 0;

#ifndef bool
typedef enum { false = 0, true = 1 } bool;
#endif

bool dfs(int i, int sum)
{
	loop_cnt++;
	if (i == ELEMENT_NUM)	/* all done */
		return sum == WANT;

	if (dfs(i + 1, sum)) {	/* without a[i] */
		b[i] = 0;
		return true;
	}

	if (dfs(i + 1, sum + a[i])) {	/* add a[i] */
		b[i] = 1;
		return true;
	}

	return false;
}

int main(int argc, char *argv[])
{
	int i;

	if (dfs(0, 0)) {
		printf("yes, %d equals sum of ", WANT);
		for (i = 0; i < ELEMENT_NUM; i++)
			if (b[i])
				printf("%d ", a[i]);
		printf("\n");
	} else
		printf("no\n");

	printf("loop count : %d\n", --loop_cnt);

	return 0;
}
