#include "../header.h"
void calculate_phi(int N, vector<ll> &phi) {
	phi.assign(N + 1, 0);
	iota(phi.begin(), phi.end(), 0); // numeric
	for (ll i = 2; i <= N; ++i) if (phi[i] == i)
		for (ll j = i; j <= N; j += i) phi[j] -= phi[j] / i;
}
