#include "../header.h"
#ifdef _MSC_VER
#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcount(x)
#endif
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
ll next_power_of_2(ll x) {	// used in FFT
	x  = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
	return x + 1;
}
ll brinc(ll x, ll k) {
	ll i = k - 1, s = 1 << i;
	x ^= s;
	if ((x & s) != s) {
		--i; s >>= 1;
		while (i >= 0 && ((x & s) == s))
			x = x &~ s, --i, s >>= 1;
		if (i >= 0) x |= s;
	}
	return x;
}
