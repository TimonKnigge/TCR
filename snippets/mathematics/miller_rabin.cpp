#include "../header.h"
#include "numbertheory.cpp"
vector<ll> test_primes  = {2,7,61};					// <= 2^32
vector<ll> test_primes2 = {2,13,23,1662803};		// <= 1.1e12
vector<ll> test_primes3 = {2,3,5,7,11,13,17,19,23};	// <= 3.8e18, v <= 2^64
vector<ll> test_primes4 = {2,325,9375,28178,450775,9780504,1795265022};
//using ll = __int128	// uncomment for n>=1e9, or use mulmod instead
bool miller_rabin(const ll n){	// true when prime
	if(n<2) return false;		
	if(n%2==0) return n==2;
	ll s = 0, d = n-1; // n-1 = 2^s * d
	while(~d&1) s++, d/=2;
	for(auto a : test_primes){
		if(a > n-2) break;
		ll x = powmod(a,d,n);
		if(x == 1 || x == n-1) continue;
		for (int i = 0; i < s - 1; ++i) {
			x = x*x%n;
			if(x==1) return false;
			if(x==n-1) goto next_it;
		}
		return false;
next_it:;
	}
	return true;
}
