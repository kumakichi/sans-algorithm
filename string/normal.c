#include <stdio.h>
#include <string.h>

int sans_index(char *full, char *want)
{
	int slen, wlen;
	int i, s = 0, w = 0;

	slen = strlen(full);
	wlen = strlen(want);

	for (s = 0; s < slen; s++) {
		if (w == wlen)
			break;

		if (full[s] == want[w]) {
			w++;
		} else {
			s -= w;	/* back to the position before this time comparasion */
			w = 0;
		}
	}

	if (w == wlen)
		return s - wlen;
	else
		return -1;
}

int main(void)
{
	int tmp;
	char *wanted = "ABCDABD";
	char *src = "BBC ABCDAB ABCDABCDABDE";

	tmp = sans_index(src, wanted);
	printf("'%s' of '%s' : %d\n", wanted, src, tmp);

	return 0;
}
