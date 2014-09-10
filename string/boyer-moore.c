#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 128
#define CHAR_INIT_VAL -1
int idx_tbl[MAX_CHARS];		/* array contains every index of element in want str */

int build_char_table(char *want, int len)
{
	int i, ret = -1;

	for (i = 0; i < MAX_CHARS; i++)
		idx_tbl[i] = CHAR_INIT_VAL;

	for (i = len - 1; i >= 0; i--) {
		if (idx_tbl[want[i]] == CHAR_INIT_VAL)
			idx_tbl[want[i]] = i;

		if (i < len - 1 && want[i] == want[len - 1])
			ret = i;
	}

	return ret;
}

int boyer_moore(char *want, int wlen, char *src, int slen, int last_occur)
{
	int w, s, good_suffix = 0;

	for (s = 0; s < slen;) {
		for (w = wlen - 1; w > 0; w--) {
			if (want[w] == src[s + w]) {
				good_suffix = 1;
			} else {
				if (good_suffix) {	/* 后移位数 = 末尾的位置 - 搜索词中上一次出现末尾字符位置 */
					s += idx_tbl[want[wlen - 1]] - last_occur;
					good_suffix = 0;
				} else {	/* 后移位数 = 坏字符的位置 - 搜索词中上一次坏字符位置 */
					s += idx_tbl[want[w]] - idx_tbl[src[s + w]];
				}
				break;
			}
		}

		if (w == 0 && good_suffix)
			return s;
	}

	return -1;
}

int main(void)
{
	char *data = "EXAMPLE";
	char *search = "HERE IS A SIMPLE EXAMPLE DONE";

	int idx, data_len, total_len, last_occur;

	data_len = strlen(data);
	total_len = strlen(search);

	last_occur = build_char_table(data, data_len);
	idx = boyer_moore(data, data_len, search, total_len, last_occur);

	if (-1 == idx)
		printf("'%s' not found in '%s'\n", data, search);
	else
		printf("found '%s' in '%s' at position %d,sub is : '%s'\n",
		       data, search, idx, search + idx);

	return 0;
}
