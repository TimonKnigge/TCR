#include "../header.h"
vi calculate_phi(int n) {
	vi phi(n + 1, 0LL);
	iota(phi.begin(), phi.end(), 0LL);
	for (ll i = 2LL; i <= n; ++i)
		if (phi[i] == i)
			for (ll j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
	return phi;
}
