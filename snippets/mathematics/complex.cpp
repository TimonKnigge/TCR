#include "../header.h"
struct Complex { using T = Complex; ld u,v;
	Complex(ld u=0, ld v=0) : u{u}, v{v} {}
	T operator+(T r) const { return {u+r.u, v+r.v}; }
	T operator-(T r) const { return {u-r.u, v-r.v}; }
	T operator*(T r) const { return {u*r.u - v*r.v, u*r.v + v*r.u}; }
	T operator/(T r) {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u*r.u + v*r.v)/norm, (v*r.u - u*r.v)/norm};
	}
	T inv(){ return T{1,0}/ *this; }
	static T root(ll k){ return {cos(2*M_PIl/k), sin(2*M_PIl/k)}; }
};
