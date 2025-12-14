#include <stdio.h>
#include <stdlib.h>

#define N 0x1000ULL
#define SQ(x) ((x)*(x))

struct jbox {
	long long x, y, z;
	struct jbox *cct;
};

struct pair {
	struct jbox *a, *b;
	long long dist2;
};

static int
cmp_size(const void *a, const void *b) {
	return *(const int *)a - *(const int *)b;
}

static int
cmp_pair(const void *a, const void *b) {
	long long da = ((const struct pair *)a)->dist2;
	long long db = ((const struct pair *)b)->dist2;
	return da > db ? 1 : da < db ? -1 : 0;
}

int
main(void) {
	static struct jbox jbox[N];
	static struct pair pair[(N-1)*(N/2)];
	static int size[N];
	long long ag, au, x, y, z;
	int n, m, i, j;
	struct jbox *a, *b, *merge;
	for (n = 0; scanf("%lld,%lld,%lld ", &x, &y, &z) == 3; n++)
		jbox[n] = (struct jbox){x, y, z, &jbox[n]};
	m = 0;
	for (a = jbox; a < jbox+n; a++)
		for (b = a+1; b < jbox+n; b++)
			pair[m++] = (struct pair){a, b,
				SQ(a->x-b->x)+SQ(a->y-b->y)+SQ(a->z-b->z)};
	qsort(pair, m, sizeof *pair, cmp_pair);
	for (i = 0; i < m; i++) {
		if (i == 1000) {
			for (j = 0; j < n; j++)
				size[jbox[j].cct - jbox]++;
			qsort(size, n, sizeof *size, cmp_size);
			ag = size[n-3]*size[n-2]*size[n-1];
		}
		a = pair[i].a; b = pair[i].b;
		if (!a->cct && !b->cct)
			a->cct = b->cct = a;
		else if (!a->cct)
			a->cct = b->cct;
		else if (!b->cct)
			b->cct = a->cct;
		else if (a->cct == b->cct)
			continue;
		else {
			merge = b->cct;
			for (j = 0; j < n; j++)
				if (jbox[j].cct == merge)
					jbox[j].cct = a->cct;
		}
		au = a->x*b->x;
	}
	printf("%lld\n%lld\n", ag, au);
}
