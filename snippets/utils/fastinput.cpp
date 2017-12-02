#include "../header.h"
int r() {
	int sign = 1, n = 0;
	char c;
	while (c = getchar_unlocked())
		switch (c) {
			case '-': sign = -1; break;
			case ' ': case '\n': return n * sign;
			default: n *= 10; n += c - '0'; break;
		}
}
// Don't forget newlines!
void print(ll x){
	char buf[20], *p=buf;
	if(!x) putchar_unlocked('0');
	else{
		while(x) *p++='0'+x%10, x/=10;
		do putchar_unlocked(*--p); while(p!=buf);
	}
}
