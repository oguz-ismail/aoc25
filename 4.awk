{
	gsub(/./, "& ")
	for (x = 1; x <= NF; x++)
		if ($x == "@")
			a[x, NR]
}
END {
	n = length(a)
	remove(a, b)
	print n-length(b)
	for (i = 0; length(a) != length(b); i++)
		if (i % 2)
			remove(a, b)
		else
			remove(b, a)
	print n-length(b)
}
function remove(a, b) {
	delete b
	for (xy in a) {
		split(xy, tmp, SUBSEP)
		x = tmp[1]
		y = tmp[2]
		if (((x+1, y+1) in a) \
		+ ((x-1, y-1) in a) \
		+ ((x+1, y-1) in a) \
		+ ((x-1, y+1) in a) \
		+ ((x+1, y) in a) \
		+ ((x-1, y) in a) \
		+ ((x, y+1) in a) \
		+ ((x, y-1) in a) >= 4)
			b[xy]
	}
}
