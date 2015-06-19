#include "../header.h"

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
int lcm(int a, int b) { return (a * (b / gcd(a, b))); }

int x, y, d; // Bézout, a*x+b*y=d
// all solutions given by
// x = x1 + k(b/d), y = y1 - k(a/d)
void euclid(int a, int b) {
	if (b == 0) { x = 1; y = 0; d = a; return; }
	euclid(b, a % b);
	int x1 = y, y1 = x - (a / b) * y;
	x = x1; y = y1;
}

