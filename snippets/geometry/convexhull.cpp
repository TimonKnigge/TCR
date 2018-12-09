#include "../header.h"
#include "essentials.cpp"
struct ConvexHull {			// O(n lg n) monotone chain.
	size_t n;
	vector<size_t> h, c;	// Indices of the hull are in `h`, ccw.
	const vector<P> &p;
	ConvexHull(const vector<P> &_p) : n(_p.size()), c(n), p(_p) {
		std::iota(c.begin(), c.end(), 0);
		std::sort(c.begin(), c.end(), [this](size_t l, size_t r) -> bool {
			return p[l].x != p[r].x ? p[l].x < p[r].x : p[l].y < p[r].y; });
		c.erase(std::unique(c.begin(), c.end(), [this](size_t l, size_t r) {
			return p[l] == p[r]; }), c.end());
		for (size_t s = 1, r = 0; r < 2; ++r, s = h.size()) {
			for (size_t i : c) {
				while (h.size() > s
						&& ccw(p[h.end()[-2]], p[h.end()[-1]], p[i]) <= 0)
					h.pop_back();
				h.push_back(i);
			}
			reverse(c.begin(), c.end());
		}
		if (h.size() > 1) h.pop_back();
	}
	size_t size() const { return h.size(); }
	template <class T, void U(const P&, const P&, const P&, T&)>
	void rotating_calipers(T &ans) {
		if (size() <= 2) U(p[h[0]], p[h.back()], p[h.back()], ans); else
		for (size_t i = 0, j = 1, s = size(); i < 2*s; ++i) {
			while (det(p[h[(i+1)%s]]-p[h[i%s]], p[h[(j+1)%s]]-p[h[j]]) >= 0)
				j = (j+1)%s;
			U(p[h[i%s]], p[h[(i+1)%s]], p[h[j]], ans);
		}
	}
};
// Example: furthest pair of points. Now set ans = 0LL and call
// ConvexHull(pts).rotating_calipers<ll, update>(ans);
void update(const P &p1, const P &p2, const P &o, ll &ans) {
	ans = max(ans, max((p1-o).lensq(), (p2-o).lensq()));
}
