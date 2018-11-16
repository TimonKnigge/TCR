#include "../header.h"
#include "./numbertheory.cpp"
template<ll p,ll w> // prime, primitive root
struct Field { using T = Field; ll x; Field(ll x=0) : x{x} {}
	T operator+(T r) const { return {(x+r.x)%p}; }
	T operator-(T r) const { return {(x-r.x+p)%p}; }
	T operator*(T r) const { return {(x*r.x)%p}; }
	T operator/(T r) const { return (*this)*r.inv(); }
	T inv() const { return {mod_inverse(x,p)}; }
	static T root(ll k) { assert( (p-1)%k==0 );		// (p-1)%k == 0?
		auto r = powmod(w,(p-1)/abs(k),p);			// k-th root of unity
		return k>=0 ? T{r} : T{r}.inv();
	}
	bool zero() const { return x == 0LL; }
};
using F1 = Field<1004535809,3 >;
using F2 = Field<1107296257,10>; // 1<<30 + 1<<25 + 1
using F3 = Field<2281701377,3 >; // 1<<31 + 1<<27 + 1
