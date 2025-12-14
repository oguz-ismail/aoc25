BEGIN {
	x = 50
}
{
	l = sub("L", "")
	sub("R", "")
	if (l && x) x = 100-x
	x += $0
	gold += x/100
	x %= 100
	if (l && x) x = 100-x
	if (x == 0) silver++
}
END {
	print silver, gold
}
