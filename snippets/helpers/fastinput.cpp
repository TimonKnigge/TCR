int r() {
	int sign = 1, n = 0;
	char c;
	while ((c = getc_unlocked(stdin)) != '\n')
		switch (c) {
			case '-': sign = -1; break;
			case ' ': case '\n': return n * sign;
			default: n *= 10; n += c - '0'; break;
		}
}
