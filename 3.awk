{
	ag += max(0, $0, 2)
	au += max(0, $0, 12)
}
END {
	print ag, au
}
function max(x, s, n,  ss, d, i) {
	ss = substr(s, 1, length(s)-(n-1))
	for (d = 9; d > 0; d--)
		if ((i = index(ss, d)))
			break
	x = x*10 + d
	return n > 1 ? max(x, substr(s, i+1), n-1) : x
}


