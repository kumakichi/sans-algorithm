#include <stdio.h>
#include <string.h>

void gen_next(char *s, int *next, int slen)
{
	int prefix, suffix;

	next[0] = 0;		/* here index of array 'next' means length of sub string of 's' */
	next[1] = 0;

/* start status: */
/*     A        B       C D A B D */
/*     |        | */
/*   prefix  suffix */

	for (prefix = 0, suffix = 1; suffix < slen; suffix++) {
		if (s[prefix] == s[suffix]) {
			next[suffix + 1] = next[suffix] + 1;  /* index of array 'next' means ... */
			prefix++;
		} else {
			next[suffix + 1] = 0;
			prefix = 0;	/* not found, back to very first of prefix(that is, offset 0) */
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
		if (want_idx == wlen)
			break;

		if (wanted[want_idx] == src[src_idx]) {
			want_idx++;
		} else {
			if (want_idx > 0) {
				src_idx -= next[want_idx] + 1;  /* here decrease addtional 1, because the 'for' loop will increase it instantly*/
				want_idx = 0;
			}
		}
	}

	if (want_idx == wlen)
		printf("found [%s] in [%s],at position : %d\n",
		       wanted, src, src_idx - wlen);
	else
		printf("not found\n");

	return 0;
}
