#include "../header.h"
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

void scan(ll &x){	// doesn't handle negative numbers
	char c;
	while((x=getchar())<'0');
	for(x-='0'; '0'<=(c=getchar()); x=10*x+c-'0');
}
void print(ll x){
	char buf[20], *p=buf;
	if(!x) putchar('0');
	else{
		while(x) *p++='0'+x%10, x/=10;
		do putchar(*--p); while(p!=buf);
	}
}
