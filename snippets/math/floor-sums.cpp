#include "../header.h"
// Computes \sum_{k=1}^N \lfloor kp/q \rfloor
ll floor_sum(ll N, ll p, ll q) {
	ll t = __gcd(p, q), s = 0, z = 1;
	p /= t, q /= t;
	while (q > 0 && N > 0) {
		t = p/q;
		s += N*(N+1)/2*z*t;
		p -= q*t, t = N/q;
		s += z*p*t*(N+1) - z*t*(p*q*t+p+q-1)/2;
		N -= q*t, t = N*p/q;
		s += z*t*N;
		N = t, swap(p, q), z *= -1;
	}
	return s;
}
// Computes #{x,y \in ZxZ | x,y > 0, ax + by \leq c}
ll count_triangle(ll a, ll b, ll c) {
	assert(a > 0 && b > 0 && c > 0);
	if (b > a) swap(a, b);
	ll m = c/a;
	if (a == b) return m*(m-1)/2;
	ll k = (a-1)/b, h = (c-a*m)/b;
	return m*(m-1)/2*k + m*h + count_triangle(b, a-b*k, c-b*(k*m+h));
}
