#include "../header.h"
constexpr double pi = 3.1415926535897932384626433; // or std::acos(-1)
struct Complex { using T = Complex; double u,v;
	Complex(double u=0, double v=0) : u{u}, v{v} {}
	T operator+(T r) const { return {u+r.u, v+r.v}; }
	T operator-(T r) const { return {u-r.u, v-r.v}; }
	T operator*(T r) const { return {u*r.u - v*r.v, u*r.v + v*r.u}; }
	T operator/(T r) const {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u*r.u + v*r.v)/norm, (v*r.u - u*r.v)/norm};
	}
	T operator*(double r) const { return T{u*r, v*r}; }
	T operator/(double r) const { return T{u/r, v/r}; }
	T inv() const { return T{1,0}/ *this; }
	T conj() const { return T{u, -v}; }
	static T root(ll k){ return {cos(2*pi/k), sin(2*pi/k)}; }
	bool zero() const { return max(abs(u), abs(v)) < 1e-6; }
};
