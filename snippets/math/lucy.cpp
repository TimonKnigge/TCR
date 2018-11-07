#include "../header.h"
ll f(ll n) { return n*n; }
ll F(ll n) { return n*(n+1)*(2*n+1)/6LL; }
ll lucy(ll n) {
	ll k = ll(sqrt(n));
	vi V;
	for (ll i = 1; i <= k; ++i) V.push_back(i), V.push_back(n/i);
	sort(V.rbegin(), V.rend());
	V.erase(unique(V.begin(), V.end()), V.end());

	unordered_map<ll, ll> S;
	for (size_t i = 0; i < V.size(); ++i)
		S[V[i]] = F(V[i]) - F(1);

	for (ll p = 2LL; p <= k; ++p)
		if (S[p] > S[p-1]) {
			ll sp = S[p-1];
			for (ll v : V)
				if (v >= p*p)
					S[v] -= f(p)*(S[v/p] - sp);
				else break;
		}
	return S[n];
}
