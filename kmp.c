#include <stdio.h>
#include <string.h>

void gen_next(char *s, int *next, int slen)
{
	int prefix, suffix;

	next[0] = 0;
	next[1] = 0;

	for (prefix = 0, suffix = 1; suffix <= slen - 2; suffix++) {
		if (s[prefix] == s[suffix]) {
			next[suffix + 1] = next[suffix] + 1;
			prefix++;
		} else {
			prefix = 0;
			next[suffix + 1] = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	char *wanted = "ABCDABD";
	char *src = "BBC ABCDAB ABCDABCDABDE";
	int want_idx, src_idx, got = 0;
	int wlen = strlen(wanted), slen = strlen(src), next[slen];

	gen_next(wanted, next, wlen);

	for (want_idx = 0, src_idx = 0; src_idx < slen; src_idx++) {
		if (wanted[want_idx] == src[src_idx]) {
			want_idx++;
			if (want_idx == wlen) {
				got = 1;
				break;
			}
		} else {
			if (want_idx > 0) {
				src_idx -= next[want_idx] + 1;
				want_idx = 0;
			}
		}
	}

	if (got)
		printf("%d\n", src_idx - wlen + 1);
	else
		printf("not found\n");

	return 0;
}
