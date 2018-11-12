#include "../header.h"
using C = ld;	// could be long long or long double
constexpr C EPS = 1e-10;	// change to 0 for C=ll
struct P {		// may also be used as a 2D vector
	C x, y;
	P(C x = 0, C y = 0) : x(x), y(y) {}
	P operator+ (const P &p) const { return {x + p.x, y + p.y}; }
	P operator- (const P &p) const { return {x - p.x, y - p.y}; }
	P operator* (C c) const { return {x * c, y * c}; }
	P operator/ (C c) const { return {x / c, y / c}; }
	C operator* (const P &p) const { return x*p.x + y*p.y; }
	C operator^ (const P &p) const { return x*p.y - p.x*y; }
	P perp() const { return P{y, -x}; }
	C lensq() const { return x*x + y*y; }
	ld len() const { return sqrt((ld)lensq()); }
	static ld dist(const P &p1, const P &p2) {
		return (p1-p2).len(); }
	bool operator==(const P &r) const {
		return ((*this)-r).lensq() <= EPS*EPS; }
};
C det(P p1, P p2) { return p1^p2; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
C det(const vector<P> &ps) {
	C sum = 0; P prev = ps.back();
	for(auto &p : ps) sum += det(p, prev), prev = p;
	return sum;
}
// Careful with division by two and C=ll
C area(P p1, P p2, P p3) { return abs(det(p1, p2, p3))/C(2); }
C area(const vector<P> &poly) { return abs(det(poly))/C(2); }
int sign(C c){ return (c > C(0)) - (c < C(0)); }
int ccw(P p1, P p2, P o) { return sign(det(p1, p2, o)); }

// Only well defined for C = ld.
P unit(const P &p) { return p / p.len(); }
P rotate(P p, ld a) { return P{p.x*cos(a)-p.y*sin(a), p.x*sin(a)+p.y*cos(a)}; }
