/:$/ {
	id = $0
}
/#/ {
	n[id] += gsub(/#/, "&")
}
/x/ {
	sub(/[x:]/, " ")
	need = $0
	for (i = 3; i <= NF; i++)
		need += $i*n[i-3 ":"]
	ag += need <= $1*$2
}
END {
	print ag
}
