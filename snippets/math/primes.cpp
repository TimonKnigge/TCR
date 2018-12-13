#include "../header.h"
#include "numbertheory.cpp"
ll SIZE;
vector<ll> primes, spf;

void sieve(ll size=1e6) {	// Initialize once in main.
	spf.assign((SIZE = size) + 1, -1);
	spf[0] = spf[1] = 1;
	for (ll i = 2; i <= SIZE; i++)
		if (spf[i] < 0) {
			spf[i] = i, primes.push_back(i);
			for (ll j = i * i; j <= SIZE; j += i)
				if (spf[j] < 0) spf[j] = i;
		}
}
bool is_prime(ll n) {
	assert(n <= SIZE*SIZE);
	if (n <= SIZE) return spf[n] == n;
	for (ll p : primes) if (n % p == 0LL) return false;
	return true;
}
struct Factor{ ll p; ll exp; };
using FS = vector<Factor>;
FS factor(ll n){ // Up to SIZE^2
	FS fs;
	for (size_t i = 0; i < primes.size() && n > SIZE; ++i)
		if (n % primes[i] == 0) {
			fs.push_back({primes[i], 0});
			while (n % primes[i] == 0)
				fs.back().exp++, n /= primes[i];
		}
	if (n <= SIZE) {
		for(; n>1; n /= spf[n]) {
			if (!fs.empty() && fs.back().p == spf[n])
				++fs.back().exp;
			else fs.push_back({spf[n], 1});
		}
	} else fs.push_back({n, 1});
	return fs;
}
