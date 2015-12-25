#include "../header.h"
#include "./numbertheory.cpp"
template<ll p,ll w> // prime, primitive root
struct Field { using T = Field; ll x; Field(ll x=0) : x{x} {}
	T operator+(T r) const { return {(x+r.x)%p}; }
	T operator-(T r) const { return {(x-r.x+p)%p}; }
	T operator*(T r) const { return {(x*r.x)%p}; }
	T inv(){ return {mod_inverse(x,p)}; }
	static T root(ll k) {	// k-th root of unity
		auto r = powmod(w,(p-1)/abs(k),p);
		return k>=0 ? T{r} : T{r}.inv();
	}
};
