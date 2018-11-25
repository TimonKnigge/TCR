#include "../header.h"
#include "./poly.h"
// x^k mod f
vector<T> xmod(const vector<T> f, ll k) {
	vector<T> r{T(1)};
	for (int b = 62; b >= 0; --b) {
		if (r.size() > 1)
			square_inplace(r), r = mod(r, f);
		if ((k>>b)&1) {
			r.insert(r.begin(), T(0));
			if (r.size() == f.size()) {
				T c = r.back() / f.back();
				for (size_t i = 0; i < f.size(); ++i)
					r[i] = r[i] - c * f[i];
				r.pop_back();
			}
		}
	}
	return r;
}
// Given A[0,k) and C[0, k), computes the n-th term of:
// A[n] = \sum_i C[i] * A[n-i-1]
T nth_term(const vector<T> &A, const vector<T> &C, ll n) {
	int k = (int)A.size();
	if (n < k) return A[n];

	vector<T> f(k+1, T{1});
	for (int i = 0; i < k; ++i)
		f[i] = T{-1} * C[k-i-1];
	f = xmod(f, n);

	T r = T{0};
	for (int i = 0; i < k; ++i)
		r = r + f[i] * A[i];
	return r;
}
