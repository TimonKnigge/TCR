#include "../header.h"
#include "./complex.cpp"
#include "./field.cpp"
void brinc(int &x, int k) {
	int i = k - 1, s = 1 << i;
	x ^= s;
	if ((x & s) != s) {
		--i; s >>= 1;
		while (i >= 0 && ((x & s) == s))
			x = x &~ s, --i, s >>= 1;
		if (i >= 0) x |= s;
	}
}
using T = Complex;	// using T=F1,F2,F3
vector<T> roots;
void root_cache(int N) {
	if (N == (int)roots.size()) return;
	roots.assign(N, T{0});
	for (int i = 0; i < N; ++i)
		roots[i] = ((i&-i) == i)
			? T{cos(2.0*pi*i/N), sin(2.0*pi*i/N)}
			: roots[i&-i] * roots[i-(i&-i)];
}
void fft(vector<T> &A, int p, bool inv = false) {
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, brinc(r, p))
		if (i < r) swap(A[i], A[r]);
//	Uncomment to precompute roots (for T=Complex). Slower but more precise.
//	root_cache(N);
//				, sh=p-1		, --sh
	for (int m = 2; m <= N; m <<= 1) {
		T w, w_m = T::root(inv ? -m : m);
		for (int k = 0; k < N; k += m) {
			w = T{1};
			for (int j = 0; j < m/2; ++j) {
//				T w = (!inv ? roots[j<<sh] : roots[j<<sh].conj());
				T t = w * A[k + j + m/2];
				A[k + j + m/2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * w_m;
			}
		}
	}
	if(inv){ T inverse = T(N).inv(); for(auto &x : A) x = x*inverse; }
}
// convolution leaves A and B in frequency domain state
// C may be equal to A or B for in-place convolution
void convolution(vector<T> &A, vector<T> &B, vector<T> &C){
	int s = A.size() + B.size() - 1;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	A.resize(N,{}); B.resize(N,{}); C.resize(N,{});
	fft(A, q, false); fft(B, q, false);
	for (int i = 0; i < N; ++i) C[i] = A[i] * B[i];
	fft(C, q, true); C.resize(s);
}
void square_inplace(vector<T> &A) {
	int s = 2*A.size()-1, q = 32 - __builtin_clz(s-1), N=1<<q;
	A.resize(N,{}); fft(A, q, false);
	for(auto &x : A) x = x*x;
	fft(A, q, true); A.resize(s);
}
