#include "../geometry/essentials.cpp"
bool lexo_yx(const P &l, const P &r) {
	return l.y != r.y ? l.y < r.y : l.x < r.x;
}
int quad(P p) {
	if (p.x > 0 && p.y >= 0) return 0;	// This `quad` is different from
	if (p.y > 0 && p.x <= 0) return 1;	// the one in planar-rotation.cpp,
	if (p.x < 0 && p.y <= 0) return 2;	// make sure to not mix the two.
	if (p.y < 0 && p.x >= 0) return 3;
	return 0; // p.x = 0 \land p.y = 0, go with 0 arbitrarily.
}
struct ConvexPolygon {
	// 21 Polygon is cut up into quadrants, where quadrant
	// 30 i is given by the segment [s[i], s[i+1])
	size_t s[5], N;
	vector<P> Ps;

	// Input a non-degenerate convex polygon. All vertices must have
	// an internal angle that is strictly less than pi.
	ConvexPolygon(const vector<P> &_Ps) : N(_Ps.size()), Ps(_Ps) {
		assert(N >= 3); size_t l = 0;
		for (size_t j = 1; j < N; ++j) l = (lexo_yx(Ps[l], Ps[j]) ? l : j);
		if (l != 0) std::rotate(Ps.begin(), Ps.begin()+l, Ps.end());
		Ps.resize(Ps.size()+3);
		std::copy(Ps.begin(), Ps.begin()+3, Ps.begin()+N);
		for (size_t i = 0; i < N; ++i) Ps.push_back(Ps[i]);
		s[0] = 0;
		for (int i = 1; i <= 4; ++i) {
			s[i] = s[i-1];
			while (s[i] < N && quad(Ps[s[i]+1] - Ps[s[i]]) < i) ++s[i];
		}
	}

	// Runs in O(lg n). Returns 1 for inside, 0 for border, -1 for outside.
	int contains(const P &p) const {	// Tested on ICPC WF J 2016
		if (p.y < Ps[s[0]].y || Ps[s[2]].y < p.y) return -1;
		{	// right hull
			size_t l = s[0], r = s[2];
			while (l < r) {
				size_t m = (l + r) / 2;
				if (Ps[m+1].y < p.y) l = m + 1; else r = m;
			}
			int side = ccw(Ps[l+1], p, Ps[l]);
			if (side < 0) return -1;
			if (side == 0) {
				if (max(Ps[l].x, Ps[l+1].x) <  p.x) return -1;
				if (min(Ps[l].x, Ps[l+1].x) <= p.x) return 0;
			}
		}{	// left hull
			size_t l = s[2], r = s[4];
			while (l < r) {
				size_t m = (l + r) / 2;
				if (Ps[m+1].y > p.y) l = m + 1; else r = m;
			}
			int side = ccw(Ps[l+1], p, Ps[l]);
			if (side < 0) return -1;
			if (side == 0) {
				if (min(Ps[l].x, Ps[l+1].x) >  p.x) return -1;
				if (max(Ps[l].x, Ps[l+1].x) >= p.x) return 0;
			}
		}
		return 1;
	}

	// Returns some i such that Ps[i] * v is maximal.
	size_t extreme(const P &v) const {	// ONLY TESTED LOCALLY
		size_t l, r;
		if (v.x > 0 || (v.x == 0LL && v.y < 0LL))
				l = s[0], r = s[2];
		else	l = s[2], r = s[4];
		while (l < r) {
			size_t m = (l + r) / 2;
			if ((Ps[m+1] - Ps[m]) * v <= 0LL)
					r = m;
			else	l = m + 1;
		}
		l %= N;
		// When there are two possible outputs, l is one of them. If l is
		// the 'largest' of the two, then this code moves to the 'smallest',
		// if it is not l (then it must be l-1). Only keep if important.
		if (Ps[(N+(l-1))%N] * v >= Ps[l] * v) l = (N+(l-1))%N;
		return l;
	}

	// Returns i such that p -> Ps[i] is right-tangent to Ps, cq j left.
	std::pair<size_t, size_t> tangent(const P &p) const {
//		Tested on ICPC WF J 2016
//		assert(this->contains(p) < 0);
		size_t rt, lt;
		{	// right tangent
			size_t l, r;
			if (p.x < Ps[s[1]].x && (p.y <= Ps[s[0]].y
					|| ccw(Ps[s[1]], p, Ps[s[0]]) < 0LL))
				l = s[0], r = s[1]; else
			if (p.y < Ps[s[2]].y && (p.x >= Ps[s[1]].x
					|| ccw(Ps[s[2]], p, Ps[s[1]]) < 0LL))
				l = s[1], r = s[2]; else
			if (p.x > Ps[s[3]].x && (p.y >= Ps[s[2]].y
					|| ccw(Ps[s[3]], p, Ps[s[2]]) < 0LL))
				l = s[2], r = s[3]; else
			if (p.y > Ps[s[4]].y && (p.x <= Ps[s[3]].x
					|| ccw(Ps[s[4]], p, Ps[s[3]]) < 0LL))
				l = s[3], r = s[4]; else assert(false);
			while (l < r) {
				size_t m = (l + r) / 2;
				if ((Ps[m+1] - Ps[m]) * (p - Ps[m]) >= 0LL
							|| ccw(Ps[m], Ps[m+1], p) < 0)
						l = m + 1;
				else	r = m;
			}
			rt = l % N;
		}{	// left tangent
			size_t l, r;
			if (p.y >= Ps[s[0]].y && (p.x > Ps[s[1]].x
					|| ccw(Ps[s[1]], p, Ps[s[0]]) < 0LL))
				l = s[0], r = s[1]; else
			if (p.x <= Ps[s[1]].x && (p.y > Ps[s[2]].y
					|| ccw(Ps[s[2]], p, Ps[s[1]]) < 0LL))
				l = s[1], r = s[2]; else
			if (p.y <= Ps[s[2]].y && (p.x < Ps[s[3]].x
					|| ccw(Ps[s[3]], p, Ps[s[2]]) < 0LL))
				l = s[2], r = s[3]; else
			if (p.x >= Ps[s[3]].x && (p.y < Ps[s[4]].y
					|| ccw(Ps[s[4]], p, Ps[s[3]]) < 0LL))
				l = s[3], r = s[4]; else assert(false);
			while (l < r) {
				size_t m = (l + r + 1) / 2;
				if ((Ps[m-1] - Ps[m]) * (p - Ps[m]) >= 0LL
							|| ccw(Ps[m], Ps[m-1], p) > 0)
						r = m - 1;
				else	l = m;
			}
			lt = l % N;
		}
		return {rt, lt};
	}
	P operator[](int i) const { return Ps[i%N]; }
	P &operator[](int i) { return Ps[i%N]; }
};
