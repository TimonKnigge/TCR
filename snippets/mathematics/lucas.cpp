#include "../header.h"
#include "./primes.cpp"
ll lucas(ll n, ll k, ll p){ // calculate (n \choose k) % p
	ll ans = 1;
	while(n){
		ll np = n%p, kp = k%p;
		if(kp > np) return 0;
		ans *= binom(np,kp);
		n /= p; k /= p;
	}
	return ans;
}
