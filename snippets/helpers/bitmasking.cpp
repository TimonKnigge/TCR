#include "../header.h"
#ifdef _MSC_VER
#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcount(x)
#endif

template<typename F>	// f(ll mask) is called
void iterate_subset(ll N, F f){for(ll mask=0; mask < 1ll<<N; ++mask) f(mask);}

template<typename F>	// f(ll mask) is called
void iterate_k_subset(ll N, ll k, F f){
	ll mask = (1ll << k) - 1;
	while (!(mask & 1ll<<N)) { f(mask);
		ll t = mask | (mask-1);
		mask = (t+1) | (((~t & -~t) - 1) >> (__builtin_ctzll(mask)+1));
	}
}

// Iterate over all subsets of a set
template<typename F>	// f(ll mask) is called
void iterate_mask_subset(ll set, F f){
	ll mask = set;
	do  f(mask), mask = (mask-1) & set;
	while (mask != set);
}

// The two functions below are used in the FFT:
ll next_power_of_2(ll x) {
	x = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4;
	x |= x >> 8; x |= x >> 16;
	return x + 1;
}

ll brinc(ll x, ll k) {
	ll I = k - 1, s = 1 << I;
	x ^= s;
	if ((x & s) != s) {
		I--; s >>= 1;
		while (I >= 0 && ((x & s) == s)) {
			x = x &~ s;
			I--;
			s >>= 1;
		}
		if (I >= 0) x |= s;
	}
	return x;
}
