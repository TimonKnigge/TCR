#include "../header.h"
struct Complex {
	long double u,v;
	Complex operator+(Complex r) const { return {u+r.u, v+r.v}; }
	Complex operator-(Complex r) const { return {u-r.u, v-r.v}; }
	Complex operator*(Complex r) const {
		return {u * r.u - v * r.v, u * r.v + v * r.u};
	}
	Complex operator/(Complex r) {
		auto norm = r.u*r.u+r.v*r.v;
		return {(u * r.u + v * r.v) / norm, (v * r.u - u * r.v) / norm};
	}
	Complex cexp(complex<ld> c){ c = exp(c); return {c.real(), c.imag()}; }
};
