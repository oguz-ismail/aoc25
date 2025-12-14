BEGIN {
	FS = "[-,]"
}
{
	silver = gold = 0
	for (i = 1; i <= NF; i += 2) {
		silver += sum2($i, $(i+1))
		gold   += sumN($i, $(i+1))
	}
	print silver, gold
}
function sum2(x, y, z, n, k, sum) {
	for (n = length(x); n <= length(y); n++) {
		if (n % 2)
			continue
		k = 10**(n/2) + 1
		z = k * 10**(n/2 - 1);
		for (; length(z) == n; z += k)
			if (z >= x && z <= y)
				sum += z
	}
	return sum
}
function sumN(x, y, z, m, n, k, sum) {
	for (n = length(x); n <= length(y); n++) {
		delete seen
		for (m = 1; m <= n/2; m++) {
			if (n % m)
				continue
			for (k = 1; length(k) != n-m+1; k++)
				k *= 10**m
			for (z = 0; length(z) != n; z += 10**(m-1))
				z *= 10**m
			for (; length(z) == n; z += k)
				if (z >= x && z <= y && !(z in seen)) {
					sum += z
					seen[z]
				}
		}
	}
	return sum
}
