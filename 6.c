#include <stdio.h>

static int
nb(const char *p, int k) {
	int x = 0;
	for (; *p == ' '; p += k);
	for (; *p >= '0' && *p <= '9'; p += k)
		x = x*10 + *p-'0';
	return x;
}

int
main(void) {
	static char s[0x8000]; /* XXX NUL-terminated */
	int n, w, i, ni, j, x;
	long long ag, au, cag, cau;
	char *p;
	n = fread(s, 1, sizeof s, stdin);
	for (w = 0; s[w++] != '\n'; );
	ag = au = 0;
	p = s + n-w;
	for (i = 0; i < w; i = ni) {
		for (ni = i+1; p[ni] == ' ' || p[ni] == '\n'; ni++);
		cag = nb(s+i, 1);
		for (j = i+w; j < n-w; j += w) {
			x = nb(s+j, 1);
			cag = p[i] == '+' ? cag+x : cag*x;
		}
		cau = nb(s+i, w);
		for (j = i+1; j < ni-1; j++) {
			x = nb(s+j, w);
			cau = p[i] == '+' ? cau+x : cau*x;
		}
		ag += cag;
		au += cau;
	}
	printf("%lld\n%lld\n", ag, au);
}
