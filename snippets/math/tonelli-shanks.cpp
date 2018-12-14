#include "../header.h"
#include "elementary-nt.cpp"
ll legendre(ll a, ll p) {
	return (powmod(a, (p-1)/2, p)+1) % p - 1;
}
// Returns a root of `a` modulo p, or -1 on failure. Note that if x>0
// is one root, n-x is the other. Exactly half of all values in
// [1..p-1] have two roots, the other half have no root.
// Runtime: O(log^2 p) if the generalized Riemann hypothesis is true.
ll sqrtp(ll a, ll p) {
	a = mod(a, p);
	if (a == 0) return 0;
	if (p == 2) return a;
	if (legendre(a, p) != 1) return -1;
	if ((p&3) == 3)				// Special cases
		return powmod(a, (p+1)/4, p);
	if ((p&7) == 5) {
		ll c = powmod(a, p/8+1, p);
		return (c*c%p == a ? c : c*powmod(2, p/4, p)%p);
	}
	ll q = p-1, s = 0, z = 1;
	while (!(q&1)) ++s, q >>= 1;
	while (legendre(z, p) != -1) ++z;
	ll x = powmod(a, (q+1)/2, p);
	for (ll c = powmod(z, q, p), t = powmod(a, q, p); t != 1;) {
		ll i = 1, t2i = t*t%p;
		while (t2i != 1) t2i = t2i*t2i%p, ++i;
		ll b = powmod(c, 1LL<<(s-i-1), p);
		x = (x*b)%p, c = (b*b)%p, t = (t*c)%p, s = i;
	}
	return x;
}
// Root modulo a prime power. Must have q = p^k for some k>1
ll sqrtp(ll a, ll p, ll q) {
	ll x = sqrtp(a, p);
	if (x < 0) return -1;
	ll r = q / p, e = (q - 2*r + 1)/2;
	return mulmod(powmod(x, r, q), powmod(a, e, q), q);
}
