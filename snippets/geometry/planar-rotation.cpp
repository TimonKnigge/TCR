#include "../header.h"
#include "../geometry/essentials.cpp"
int quad(P p) {
	if (p.x >= 0 && p.y >= 0) return 0;
	if (p.x <= 0 && p.y >= 0) return 1;
	if (p.x <= 0 && p.y <= 0) return 2;
	if (p.x >= 0 && p.y <= 0) return 3;
	__builtin_unreachable();
}

struct pr { size_t i, j; };
void rotate(const vector<P> &pts) {
	size_t n = pts.size();
	vector<pr> prs;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			if (i != j) prs.push_back(pr{i, j});

	sort(prs.begin(), prs.end(), [&pts](const pr &l, const pr &r) {
		if (quad(pts[l.j]-pts[l.i]) != quad(pts[r.j]-pts[r.i]))
			return quad(pts[l.j]-pts[l.i]) < quad(pts[r.j]-pts[r.i]);
		else
			return ccw(pts[l.j]-pts[l.i], pts[r.j]-pts[r.i], P{0, 0}) > 0;
	});

	vector<size_t> vs(n), vsi(n);
	for (size_t i = 0; i < vs.size(); ++i) vs[i] = i;
	sort(vs.begin(), vs.end(), [&pts](const size_t &i, const size_t &j) {
		return pts[i].y != pts[j].y ? pts[i].y<pts[j].y : pts[i].x<pts[j].x;
	});
	for (size_t i = 0; i < vs.size(); ++i) vsi[vs[i]] = i;
	for (pr p : prs) {
		// Consider the line through pts[p.i] and pts[p.j]. All points
		// are currently sorted along the projection onto the normal.
		// Furthermore, these points are located next to each other at
		// positions vsi[p.i] and vsi[p.j].
		swap(vs[vsi[p.i]], vs[vsi[p.j]]);
		swap(vsi[p.i], vsi[p.j]);
	}
}
