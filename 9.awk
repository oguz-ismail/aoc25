BEGIN {
	FS = ","
}
{
	x[NR] = $1
	y[NR] = $2
}
END {
	for (i = 1; i <= NR; i++)
	 for (j = i+1; j <= NR; j++) {
		area = (abs(x[i]-x[j])+1)*(abs(y[i]-y[j])+1)
		if (area > ag)
			ag = area
		if (area > au) {
			for (k = 1; k <= NR; k++)
				if (skip = cut(i, j, k, k < NR ? k+1 : 1))
					break
			if (skip)
				continue
			au = area
		}
	 }
	print ag, au
}
function abs(x){
	return x < 0 ? -x : x
}
function cut(a, b, c, d) {
	return x[c] == x[d] \
	? (x[c] > x[a]) != (x[c] > x[b]) && ( \
		(y[c] > y[a]) != (y[d] > y[a]) ||
		(y[c] > y[b]) != (y[d] > y[b])) \
	: (y[c] > y[a]) != (y[c] > y[b]) && ( \
		(x[c] > x[a]) != (x[d] > x[a]) ||
		(x[c] > x[b]) != (x[d] > x[b]))
}
