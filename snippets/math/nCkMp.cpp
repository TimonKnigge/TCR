#include "../header.h"
// Requires ll modpow(ll a, ll b, ll m);
template <ll N>
struct nCkMp {
	ll p, phi;
	vi ds, fac, ifac;
	vvi cs;
	nCkMp(ll _p) : p(_p), phi(_p), fac(N+1, 1LL), ifac(N+1, 1LL), cs(N+1) {
		for (int d = 2; d * d <= _p; ++d) {
			if (_p % d != 0) continue;
			ds.push_back(d);
			while (_p % d == 0) _p /= d;
		}
		if (_p > 1) ds.push_back(_p);
		for (ll d : ds) phi = phi / d * (d - 1);
		cs[0].assign(ds.size(), 0LL);
		for (ll i = 1LL; i <= N; ++i) {
			cs[i] = cs[i-1];
			ll nd = i;
			for (size_t j = 0; j < ds.size(); ++j)
				while (nd % ds[j] == 0) ++cs[i][j], nd /= ds[j];
			fac[i] = (nd * fac[i - 1]) % p;
			ifac[i] = modpow(fac[i], phi - 1, p);
		}
	}
	// 0 <= k, n <= N
	ll nCk(ll n, ll k) {
		if (n < k) return 0LL;
		ll ans = fac[n] * ifac[k] % p * ifac[n-k] % p;
		for (size_t j = 0; j < ds.size(); ++j)
			ans = ans * modpow(ds[j], cs[n][j] - cs[k][j] - cs[n-k][j], p) % p;
		return ans;
	}
};

