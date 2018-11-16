#include "../header.h"
#include "../elementary-nt.h"
using ull = unsigned long long;
ull diff(ull x, ull y) { return x > y ? x-y : y-x; }
ull g(ull x, ull a, ull n) { return (mulmod(x, x, n) + a) % n; }

ull pollard_rho(ull n, int reps = 10) {
	if (1&~n) return 2;
	for (ull a; reps-- > 0;) {
		do { a = rand() % 2321 + 47; } while (a == n - 2);
		ull x = 2+rand()%n, y = x, d = 1;
		while (d == 1)
			x = g(x, a, n), y = g(g(y, a, n), a, n), d = gcd(diff(x, y), n);
		if (d < n) return d;
	}
	return n;
}
