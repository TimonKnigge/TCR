#include "../header.h"
ll binom(ll n, ll k){
	ll ans = 1;
	for(ll i = 1; i <= min(k,n-k); ++i) ans = ans*(n+1-i)/i;
	return ans;
}
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
