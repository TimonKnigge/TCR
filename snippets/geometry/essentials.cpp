#include "../header.h"
constexpr long double ESP = 1e-10;
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
struct S {
	P p1, p2;
	S(P p1 = 0, P p2 = 0) : p1(p1), p2(p2) {}
};
struct L{
	C a,b,c; // ax + by + c = 0
	L(C a = 0, C b = 0, C c = 0) : a(a), b(b), c(c) {}
	L(S s) : a(s.p2.y-s.p1.y), b(s.p1.x-s.p2.x),
	c(s.p2.x*s.p1.y - s.p2.y*s.p1.x) {}
};

C dist(P p1, P p2) { return (p1-p2).len(); }
C det(P p1, P p2) { return p1.x * p2.y - p1.y * p2.x; }
C det(P p1, P p2, P o) { return det(p1-o, p2-o); }
C det(vector<P> pts) {
	C sum = 0;
	REP(i,pts.size()) sum += det(pts[i], pts[(i+1)%pts.size()]);
	return sum;
}

double area(P p1, P p2, P p3) { return abs(det(p1, p2, p3)) / 2.0; }
double area(vector<P> polygon) { return abs(det(polygon)) / 2.0; }

// 1 when p1-p2-p3 is a left turn (when viewed from p1) [use EPS if needed]
int ccw(P p1, P p2, P p3) { C d = det(p1, p2, p3); return (d>0) - (d<0); }

P project(S s, P p) {
	double lambda = (p - s.p1).dot(s.p2 - s.p1)/double((s.p2 - s.p1).dot(s.p2 - s.p1));
	case LType.SEGMENT: lambda = min(1.0, lambda);
	case LType.RAY:	 lambda = max(0.0, lambda);
	default: break;
	}
	return l.p1 + (l.p2 - l.p1) * lambda;
}

bool intersect_Ls(L l1, L l2, double* lambda, LType type) {
	// Intersection P can be reconstructed as l1.p1 + lambda * (l1.p2 - l1.p1).
	// Returns false if the Ls are parallel, handle coincidence in advance.
	C s1x, s1y, s2x, s2y;
	s1x = l1.p2.x - l1.p1.x;	s1y = l1.p2.y - l1.p1.y;
	s2x = l2.p2.x - l2.p1.x;	s2y = l2.p2.y - l2.p1.y;
	C denom = det(s1x, s1y, s2x, s2y);
	if (denom == 0) return false;
	else{
		double l = det(s1x, s1y, l1.p1.x - l2.p1.x, l1.p1.y - l2.p1.y)/((double)denom),
			   m = det(s2x, s2y, l1.p1.x - l2.p1.x, l1.p1.y - l2.p1.y)/((double)denom);
		switch(type){
		case LType.SEGMENT:  if(l > 1 || m > 1) return false;
		case LType.RAY:	  if(l < 0 || m < 0) return false;
		default: break;
		}
		*lambda = l;
		return true;
	}
}
