#include "../header.h"
#include "./complex.cpp"
#include "./field.cpp"
ll next_power_of_2(ll x) {
	x  = (x - 1) | ((x - 1) >> 1);
	x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
	return x + 1;
}
ll brinc(ll x, ll k) {
	ll i = k - 1, s = 1 << i;
	x ^= s;
	if ((x & s) != s) {
		--i; s >>= 1;
		while (i >= 0 && ((x & s) == s))
			x = x &~ s, --i, s >>= 1;
		if (i >= 0) x |= s;
	}
	return x;
}
using T = Complex;	// using T=F1,F2,F3
void fft(vector<T> &A, int p, bool inv = false) {
	int N = 1<<p;
	for(int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
		if (i < r) swap(A[i], A[r]);
	for (int m = 2; m <= N; m <<= 1) {
		T w, w_m = T::root(inv ? -m : m);
		for (int k = 0; k < N; k += m) {
			w = T{1};
			for (int j = 0; j < m/2; ++j) {
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
void convolution(vector<vector<T>> &ps, vector<T> &C){
	int s=1; for(auto &p : ps) s+=p.size()-1;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	C.assign(N,{1});
	for(auto &p : ps){ p.resize(N,{}); fft(p, q, false);
		for(int i = 0; i < N; ++i) C[i] = C[i] * p[i];
	}
	fft(C, q, true); C.resize(s);
}
void square_inplace(vector<T> &A) {
	int s = 2*A.size()-1, q = 32 - __builtin_clz(s-1), N=1<<q;
	A.resize(N,{}); fft(A, q, false);
	for(auto &x : A) x = x*x;
	fft(A, q, true); A.resize(s);
}
