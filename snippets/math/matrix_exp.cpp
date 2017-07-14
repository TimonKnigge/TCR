#include "../header.h"
#define ITERATE_MATRIX(w) for (int r = 0; r < (w); ++r) \
						  for (int c = 0; c < (w); ++c)
template <class T, int N>
struct M {
	array<array<T,N>,N> m;
	M() { ITERATE_MATRIX(N) m[r][c] = 0; }
	static M id() {
		M I; for (int i = 0; i < N; ++i) I.m[i][i] = 1; return I;
	}
	M operator*(const M &rhs) const {
		M out;
		ITERATE_MATRIX(N) for (int i = 0; i < N; ++i)
				out.m[r][c] += m[r][i] * rhs.m[i][c];
		return out;
	}
	M raise(ll n) const {
		if(n == 0) return id();
		if(n == 1) return *this;
		auto r = (*this**this).raise(n / 2);
		return (n%2 ? *this*r : r);
	}
};
