!S {
	if ((S = index($0, "S")))
		n[S] = 1
	next
}
/\^/ {
	gsub(/./, "& ")
	delete tmp
	for (i in n)
		if ($i == "^") {
			tmp[i-1] += n[i]
			tmp[i+1] += n[i]
			ag++
		}
		else {
			tmp[i] += n[i]
		}
	delete n
	for (i in tmp)
		n[i] = tmp[i]
}
END {
	for (i in n)
		au += n[i]
	print ag, au
}
