#include "../header.h"
#include "../helpers/bitmasking.cpp"
#include "./complex.cpp"
#include "./field.cpp"
using T = Field<1004535809,702606812>; //using T = Complex;
void fft(vector<T> &A, int N, int p, bool inv = false) {
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
	if (inv){
		T inverse = T(N).inv();
		for(auto &x : A) x = x*inverse;
	}
}
void convolution(vector<T> &A, vector<T> &B, vector<T> &C){
	int q = 32 - __builtin_clz(A.size() + B.size() - 2), N=1<<q;
	A.resize(N,{}); B.resize(N,{}); C.resize(N,{});
	fft(A, N, q, false); fft(B, N, q, false);
	for (int i = 0; i < N; ++i) C[i] = A[i] * B[i];
	fft(C, N, q, true);
}
void convolution(vector<vector<T>> &ps, vector<T> &C){
	int ts=0; for(auto &p : ps) ts+=p.size(); ts-=ps.size()-1;
	int q = 32-__builtin_clz(ts-1), N=1<<q;	// fails if ts=1
	C.assign(N,{1});
	for(auto &p : ps) p.resize(N,{}),
		fft(p,N,q,false),
		transform(p.begin(),p.end(),C.begin(),C.begin(), multiplies<T>());
	fft(C, N, q, true); C.resize(ts);
}

void square_inplace(vector<T> &A) {
	int q = 32 - __builtin_clz(2*A.size() - 2), N=1<<q;
	A.resize(N,{});
	fft(A, N, q, false);
	for(auto &x : A) x = x*x;
	fft(A, N, q, true);
}
