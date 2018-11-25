#include "../header.h"
#include "./fft.h"
vector<T> &rev(vector<T> &A) { reverse(A.begin(), A.end()); return A; }
void copy_into(const vector<T> &A, vector<T> &B, size_t n) {
	std::copy(A.begin(), A.begin()+min({n, A.size(), B.size()}), B.begin());
}

// Multiplicative inverse of A modulo x^n. Requires A[0] != 0!!
vector<T> inverse(const vector<T> &A, int n) {
	vector<T> Ai{A[0].inv()};
	for (int k = 0; (1<<k) < n; ++k) {
		vector<T> As(4<<k, T(0)), Ais(4<<k, T(0));
		copy_into(A, As, 2<<k); copy_into(Ai, Ais, Ai.size());
		fft(As, k+2, false); fft(Ais, k+2, false);
		for (int i = 0; i < (4<<k); ++i) As[i] = As[i]*Ais[i]*Ais[i];
		fft(As, k+2, true); Ai.resize(2<<k, {});
		for (int i = 0; i < (2<<k); ++i) Ai[i] = T(2) * Ai[i] - As[i];
	}
	Ai.resize(n);
	return Ai;
}
// Polynomial division. Returns {Q, R} such that A = QB+R, deg R < deg B.
// Requires that the leading term of B is nonzero.
pair<vector<T>, vector<T>> divmod(const vector<T> &A, const vector<T> &B) {
	size_t n = A.size()-1, m = B.size()-1;
	if (n < m) return {vector<T>(1, T(0)), A};

	vector<T> X(A), Y(B), Q, R;
	convolution(rev(X), Y = inverse(rev(Y), n-m+1), Q);
	Q.resize(n-m+1); rev(Q);

	X.resize(Q.size()), copy_into(Q, X, Q.size());
	Y.resize(B.size()), copy_into(B, Y, B.size());
	convolution(X, Y, X);

	R.resize(m), copy_into(A, R, m);
	for (size_t i = 0; i < m; ++i) R[i] = R[i] - X[i];
	while (R.size() > 1 && R.back().zero()) R.pop_back();
	return {Q, R};
}
vector<T> mod(const vector<T> &A, const vector<T> &B) {
	return divmod(A, B).second;
}
