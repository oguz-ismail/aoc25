BEGIN {
	FS = "-"
}
NF == 2 {
	delete del
	for (i in lo) {
		if ($1 > hi[i] || $2 < lo[i])
			continue
		if ($1 >= lo[i] && $2 <= hi[i])
			next
		$1 = $1 > lo[i] ? lo[i] : $1
		$2 = $2 < hi[i] ? hi[i] : $2
		del[i]
	}
	for (i in del) {
		delete lo[i]
		delete hi[i]
	}
	lo[NR] = $1
	hi[NR] = $2
}
NF == 1 {
	for (i in lo)
		ag += $1 >= lo[i] && $1 <= hi[i]
}
END {
	for (i in lo)
		au += hi[i]-lo[i] + 1
	print ag, au
}
