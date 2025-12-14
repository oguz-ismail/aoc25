BEGIN {
	FS = ": | "
}
{
	for (i = 2; i <= NF; i++)
		input[$i, ++n[$i]] = $1
}
END {
	print paths("you", "out")
	print paths("svr", "fft") \
		* paths("fft", "dac") \
		* paths("dac", "out")
}
function paths(src, dst,  i, x, y) {
	delete count
	delete adj
	count[dst] = 1
	adj[dst]
	while (length(adj)) {
		delete buf
		for (x in adj) {
			for (i = 1; i <= n[x]; i++) {
				y = input[x, i]
				count[y] += count[x]
				buf[y]
			}
			if (x != src)
				delete count[x]
		}
		delete adj
		for (x in buf)
			adj[x]
	}
	return count[src]
}
