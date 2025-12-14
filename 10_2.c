/* C implementation of the algorithm described here
 * https://old.reddit.com/r/adventofcode/comments/1pk87hl */

#include <stdio.h>
#include <string.h>

#define N 0x30000
static struct {
	int jolt[10], min;
} lut[N];

static struct {
	int inc[10], n;
} btn[0x400];
static int n;
static int jolt[10], m;

static int *
lkup(void) {
	unsigned i, j;
	i = jolt[0];
	for (j = 1; j < m; j++)
		i = jolt[j] + (i << 6)+(i << 16)-i;
	for (; i %= N, lut[i].min; i++) {
		for (j = 0; j < m; j++)
			if (lut[i].jolt[j] != jolt[j])
				break;
		if (j == m)
			break;
	}
	if (!lut[i].min)
		for (j = 0; j < m; j++)
			lut[i].jolt[j] = jolt[j];
	return &lut[i].min;
}

static int
solve(void) {
	int i, j, *min, cur;
	if (*(min = lkup()))
		return *min;
	*min = 0x7fff;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			if (btn[i].inc[j] > jolt[j] ||
			    btn[i].inc[j]%2 != jolt[j]%2)
				break;
		if (j != m)
			continue;
		for (j = 0; j < m; j++)
			jolt[j] -= btn[i].inc[j];
		cur = btn[i].n;
		for (j = 0; j < m; j++)
			if (jolt[j])
				break;
		if (j != m) {
			for (j = 0; j < m; j++)
				jolt[j] /= 2;
			cur += 2*solve();
			for (j = 0; j < m; j++)
				jolt[j] *= 2;
		}
		if (cur < *min)
			*min = cur;
		for (j = 0; j < m; j++)
			jolt[j] += btn[i].inc[j];
	}
	return *min;
}

int
main(void) {
	int ans, i, j, k;
	ans = 0;
	while (getchar() == '[') {
		while (getchar() != ']');
		memset(btn, 0, sizeof btn);
		/* need a button that only divides by 2 */
		n = 1;
		while ((void)getchar(), getchar() == '(') {
			do
				btn[n].inc[getchar()-'0'] = 1;
			while (getchar() == ',');
			btn[n].n = 1;
			/* combinations */
			k = n++;
			for (i = k; i-- > 1; n++) {
				btn[n] = btn[k];
				for (j = 0; j < 10; j++)
					btn[n].inc[j] += btn[i].inc[j];
				btn[n].n += btn[i].n;
			}
		}
		m = 0;
		do
			scanf("%d", &jolt[m++]);
		while (getchar() == ',');
		(void)getchar();
		ans += solve();
		memset(lut, 0, sizeof lut);
	}
	printf("%d\n", ans);
}
