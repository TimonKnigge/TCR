#include "../header.h"
template<typename F>	// All subsets of {0..N-1}
void iterate_subset(ll N, F f){for(ll mask=0; mask < 1ll<<N; ++mask) f(mask);}
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
