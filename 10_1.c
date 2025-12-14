#include <stdio.h>

static unsigned btn[16], n, msk;

static int
solve(void) {
	static struct {
		unsigned msk, n;
	} q[0x400];
	int m, i, j, k;
	q[0].msk = msk;
	q[0].n = 0;
	m = 1;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			q[m] = q[i];
			q[m].msk ^= btn[j];
			q[m].n++;
			if (!q[m].msk)
				return q[m].n;
			for (k = 0; k < m; k++)
				if (q[k].msk == q[m].msk)
					break;
			if (k == m)
				m++;
		}
}

int
main(void) {
	int ans, i, c;
	ans = 0;
	while (getchar() == '[') {
		msk = 0;
		for (i = 0; (c = getchar()) != ']'; i++)
			msk |= (c == '#') << i;
		n = 0;
		while ((void)getchar(), getchar() == '(') {
			btn[n] = 0;
			do
				btn[n] |= 1 << (getchar()-'0');
			while (getchar() == ',');
			n++;
		}
		while (getchar() != '\n');
		ans += solve();
	}
	printf("%d\n", ans);
}
