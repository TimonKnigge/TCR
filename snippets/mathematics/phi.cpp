#include "../header.h"
void calculate_phi(int n, vector<ll> &phi) {
	phi.resize(n);
	iota(phi.begin(), phi.end(), 0); // numeric
	for (ll i=2; i<=n; ++i) if (phi[i] == i)
		for (ll j=i; j<=n; j+=i) phi[j] -= phi[j]/i;
}
