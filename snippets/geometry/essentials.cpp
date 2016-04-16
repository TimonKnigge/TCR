#include "../header.h"
constexpr long double EPS = 1e-10;
using C = double;	// could be long long or long double
struct P {			// may also be used as a vector
	C x, y;
	P(C x = 0, C y = 0) : x(x), y(y) {}
	P operator+ (const P &p) const { return {x + p.x, y + p.y}; }
	P operator- (const P &p) const { return {x - p.x, y - p.y}; }
	P operator* (C c) const { return {x * c, y * c}; }
	P operator/ (C c) const { return {x / c, y / c}; }
	bool  operator==(const P &r) const { return y == r.y && x == r.x; }
	C dot(const P &p) const { return x * p.x + y * p.y; }
	C lensq() const { return x*x + y*y; }
	C len() const { return sqrt(lensq()); }
};

C dist(P p1, P p2) { return (p1-p2).len(); }
C det(P p1, P p2) { return p1.x * p2.y - p1.y * p2.x; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
C det(vector<P> pts) {
	C sum = 0;
	for (size_t i = 0; i < pts.size(); ++i) sum += det(pts[i], pts[(i+1)%pts.size()]);
	return sum;
}

double area(P p1, P p2, P p3) { return abs(det(p1, p2, p3)) / 2.0; }
double area(vector<P> polygon) { return abs(det(polygon)) / 2.0; }

// 1 when p1-p2-p3 is a left turn (when viewed from p1) [use EPS if needed]
int ccw(P p1, P p2, P p3) { C d = det(p1, p2, p3); return (d>0) - (d<0); }
struct S {
	P p1, p2;
	enum Type { Segment, Ray, Line } type;
	S(P p1 = 0, P p2 = 0, Type type = Line) : p1(p1), p2(p2), type(type) {}
	bool internal(P p) const {
		if(det(p1,p2,p) > EPS) return false; // not on a line
		switch(type){
		case Segment: return dist(p1, p) + dist(p, p2) - dist(p1,p2) <= EPS;
		case Ray: return dist(p,p2) - abs(dist(p1,p) - dist(p1,p2)) <= EPS;
		default: return true;
		}
	}
};
struct L{
	C a,b,c; // ax + by + c = 0
	L(C a = 0, C b = 0, C c = 0) : a(a), b(b), c(c) {}
	L(S s) : a(s.p2.y-s.p1.y), b(s.p1.x-s.p2.x),
	c(s.p2.x*s.p1.y - s.p2.y*s.p1.x) {}
	operator S(){
		S s; s.type = S::Line;
		if(abs(a)<EPS) s.p1 = {0, -c/b}, s.p2 = {1, -c/b};
		else s.p1 = {-c/a, 0}, s.p2 = {-(c+b)/a, 1};
		return s;
	}
};
struct Circle{ P p; C r; };
P project(S s, P p) {
	double l = (p-s.p1).dot(s.p2-s.p1)/double((s.p2-s.p1).dot(s.p2-s.p1));
	switch(s.type){
	case S::Segment: l = min(1.0, l);
	case S::Ray:	 l = max(0.0, l);
	default:;
	}
	return s.p1 + (s.p2 - s.p1) * l;
}
pair<bool,P> intersect(const L &l1, const L &l2) {
	double x = l1.b*l2.c-l1.c*l2.b, y = l1.c*l2.a-l1.a*l2.c,
		   z = l1.a*l2.b-l1.b*l2.a;
	return {z!=0, {x/z, y/z}}; 
}
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
