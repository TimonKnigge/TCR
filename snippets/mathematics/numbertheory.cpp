#include "../header.h"
ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b;				 }
ll mod(ll a, ll b) { return ((a % b) + b) % b;				   }

// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}

// solves ab = 1 (mod n), -1 on failure
ll mod_inverse(ll a, ll n) {
	ll x, y, d;
	extended_euclid(a, n, x, y, d);
	return (d > 1 ? -1 : mod(x, n));
}

// (a*b)%m
ll mulmod(ll a, ll b, ll m){
	ll x = 0, y=a%m;
	while(b>0){
		if(b&1)
			x = (x+y)%m;
		y = (2*y)%m;
		b/=2;
	}
	return x % m;
}

// Finds a^n % m in O(lg n) time, ensure that a < m to avoid overflow!
ll powmod(ll a, ll n, ll m) {
	if (n == 0) return 1;
	if (n == 1) return a;
	ll aa = (a*a)%m; // use mulmod when b > 1e9
	if (n % 2 == 0) return powmod(aa, n / 2, m);
	return (a * powmod(aa, (n - 1) / 2, m)) % m;
}

// Solve ax + by = c, returns false on failure.
bool linear_diophantine(ll a, ll b, ll c, ll &x, ll &y) {
	ll d = gcd(a, b);
	if (c % d) {
		return false;
	} else {
		x = c / d * mod_inverse(a / d, b / d);
		y = (c - a * x) / b;
		return true;
	}
}

// Chinese remainder theorem: finds z s.t. z % xi = ai. z is
// unique modulo M = lcm(xi). Returns (z, M), m = -1 on failure.
ii crt(ll x1, ll a1, ll x2, ll a2) {
	ll s, t, d;
	extended_euclid(a1, a2, s, t, d);
	if ((x1-x2) % d != 0) return {0, -1};
	return {mod(s*x2*a1 + t*x1*a2, a1*a2)/d, a1/d*a2};
}
ii crt(vi &x, vi &a){		// ii = pair<long,long>!
	ii ret = ii(a[0], x[0]);
	for (size_t i = 1; i < x.size(); ++i) {
		ret = crt(ret.second, ret.first, x[i], a[i]);
		if (ret.second == -1) break;
	}
	return ret;
}

ll binom(ll n, ll k){
	ll ans = 1;
	for(ll i = 1; i <= min(k,n-k); i++) ans *= (n-k+i), ans/=i;
	return ans;
}
