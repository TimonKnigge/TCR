#include "../header.h"
#include "./elementary-nt.cpp"
// Solves x = a1 mod m1, x = a2 mod m2, x is unique modulo lcm(m1, m2).
// Returns {0, -1} on failure, {x, lcm(m1, m2)} otherwise.
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
	ll s, t, d;
	extended_euclid(m1, m2, s, t, d);
	if (a1 % d != a2 % d) return {0, -1};
	return {mod(s*a2 %m2 * m1 + t*a1 %m1 * m2, m1 * m2) / d, m1 / d * m2};
}

// Solves x = ai mod mi. x is unique modulo lcm mi.
// Returns {0, -1} on failure, {x, lcm mi} otherwise.
pair<ll, ll> crt(vector<ll> &a, vector<ll> &m) {
	pair<ll, ll> res = {a[0], m[0]};
	for (ull i = 1; i < a.size(); ++i) {
		res = crt(res.first, res.second, mod(a[i], m[i]), m[i]);
		if (res.second == -1) break;
	}
	return res;
}

