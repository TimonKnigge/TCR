#include "../header.h"
ll f(ll n) { return n; }
ll F(ll n) { return n*(n+1)/2LL; } // = \sum_{i \leq n} f(i)
size_t id(ll i, ll N, const vi &V) {
	return i <= V.size()/2 ? V.size()-i : N/i-1;
}	// When adding 0 to V, add a -1 ^ here.
ll lucy(ll N) {
	vi V, S;
	for (ll i = 1; i <= N; i = N/(N/i)+1)
		V.push_back(N/i), S.push_back(F(N/i)-F(1));
	for (ll p = 2LL, sp; p*p <= N; ++p)
		if (S[id(p, N, V)] > (sp = S[id(p-1, N, V)]))
			for (size_t i = 0; i < V.size() && V[i] >= p*p; ++i)
				S[i] -= f(p)*(S[id(V[i]/p, N, V)] - sp); // <= UPDATE
	return S[0]; // Or return all of S for summation upto all N/k.
}
