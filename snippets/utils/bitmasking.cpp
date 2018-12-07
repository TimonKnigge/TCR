#include "../header.h"
template<typename F>	// All subsets of size k of {0..N-1}
void iterate_k_subset(ll N, ll k, F f){
	ll mask = (1ll << k) - 1;
	while (!(mask & 1ll<<N)) { f(mask);
		ll t = mask | (mask-1);
		mask = (t+1) | (((~t & -~t) - 1) >> (__builtin_ctzll(mask)+1));
	}
}
template<typename F>	// All subsets of set
void iterate_mask_subset(ll set, F f){ ll mask = set;
	do  f(mask), mask = (mask-1) & set;
	while (mask != set);
}
int logfloor(unsigned long long a) {
	return __builtin_clzll(1) - __builtin_clzll(a);
}
