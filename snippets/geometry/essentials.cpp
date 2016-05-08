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
	bool operator==(const P &r) const { return y == r.y && x == r.x; }
	C lensq() const { return x*x + y*y; }
	C len() const { return sqrt(lensq()); }
};
C sq(C x){ return x*x; }
C dot(P p1, P p2){ return p1.x*p2.x + p1.y*p2.y; }
C dist(P p1, P p2) { return (p1-p2).len(); }
C det(P p1, P p2) { return p1.x * p2.y - p1.y * p2.x; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
C det(vector<P> ps) {
	C sum = 0; P prev = ps.back();
	for(auto &p : ps) sum+=det(p,prev), prev=p;
	return sum;
}
C area(P p1, P p2, P p3) { return abs(det(p1, p2, p3))/C(2); }
C area(vector<P> poly) { return abs(det(poly))/C(2); }
int sign(C c){ return (c > C(0)) - (c < C(0)); }
int ccw(P p1, P p2, P p3) { return sign(det(p1, p2, p3)); }
// bool: non-parallel (P is valid), p = a*l1+(1-a)*l2 = b*r1 + (1-b)*r2
pair<bool,P> intersect(P l1, P l2, P r1, P r2, ld &a, ld &b, bool &intern){
	P dl = l2-l1, dr = r2-r1; ld d = det(dl,dr);
	if(abs(d)<=EPS) return {false,{0,0}};	// parallel
	C x = det(l1,l2)*(r1.x-r2.x) - det(r1,r2)*(l1.x-l2.x);
	C y = det(l1,l2)*(r1.y-r2.y) - det(r1,r2)*(l1.y-l2.y);
	P p = {x/d, y/d}; a = det(r1-l1,dr)/d; b = det(r1-l1,dl)/d;
	intern = 0<= a && a <= 1 && 0 <= b && b <= 1;
	return {true,p};
}
P project(P p1, P p2, P p){	 // Project p on the line p1-p2
	return p1 + (p2-p1) * dot(p-p1,p2-p1)/(p2-p1).lensq(); }
P reflection(P p1, P p2, P p){ return project(p1,p2,p)*2-p; }
struct L {		// also a 3D point
	C a, b, c;	// ax + by + cz = 0
	L(C a = 0, C b = 0, C c = 0) : a(a), b(b), c(c) {}
	L(P p1, P p2) : a(p2.y-p1.y), b(p1.x-p2.x), c(p2.x*p1.y - p2.y*p1.x) {}
	void to_points(P &p1, P &p2){
		if(abs(a)<=EPS) p1 = {0, -c/b}, p2 = {1, -(c+a)/b};
		else p1 = {-c/a, 0}, p2 = {-(c+b)/a, 1};
	}
};
L cross(L p1, L p2){
	return {p1.b*p2.c-p1.c*p2.b, p1.c*p2.a-p1.a*p2.c, p1.a*p2.b-p1.b*p2.a};
}
pair<bool,P> intersect(L l1, L l2) {
	L p = cross(l1,l2);
	return {p.c!=0, {p.a/p.c, p.b/p.c}};
}

struct Circle{ P p; C r; };
vector<P> intersect(const Circle& cc, const L& l){
	const double &x = cc.p.x, &y = cc.p.y, &r = cc.r, &a=l.a,&b=l.b,&c=l.c;
	double n = a*a + b*b, t1 = c + a*x + b*y, D = n*r*r  - t1*t1;
	if(D<0) return {};
	double xmid = b*b*x - a*(c + b*y), ymid = a*a*y - b*(c + a*x);
	if(D==0) return {P{xmid/n, ymid/(n)}};
	double sd = sqrt(D);
	return {P{(xmid - b*sd)/n,(ymid + a*sd)/n},
		    P{(xmid + b*sd)/n,(ymid - a*sd)/n}};
}
vector<P> intersect(const Circle& c1, const Circle& c2){
	C x = c1.p.x-c2.p.x, y = c1.p.y-c2.p.y;
	const C &r1 = c1.r, &r2 = c2.r;
	C n = x*x+y*y, D = -(n - (r1+r2)*(r1+r2))*(n - (r1-r2)*(r1-r2));
	if(D<0) return {};
	C xmid = x*(-r1*r1+r2*r2+n), ymid = y*(-r1*r1+r2*r2+n);
	if(D==0) return {P{c2.p.x + xmid/(2.*n),c2.p.y + ymid/(2.*n)}};
	double sd = sqrt(D);
	return {P{c2.p.x + (xmid - y*sd)/(2.*n),c2.p.y + (ymid + x*sd)/(2.*n)},
			P{c2.p.x + (xmid + y*sd)/(2.*n),c2.p.y + (ymid - x*sd)/(2.*n)}};
}
