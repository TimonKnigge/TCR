#include "../header.h"
#include "./fft.cpp"
void convolution_mod(const vi &A, const vi &B, ll MOD, vi &C) {
	int s = A.size() + B.size() - 1; ll m15 = (1LL<<15)-1LL;
	int q = 32 - __builtin_clz(s-1), N=1<<q;	// fails if s=1
	vector<T> Ac(N), Bc(N), R1(N), R2(N);
	for (size_t i = 0; i < A.size(); ++i) Ac[i] = T{A[i]&m15, A[i]>>15};
	for (size_t i = 0; i < B.size(); ++i) Bc[i] = T{B[i]&m15, B[i]>>15};
	fft(Ac, q, false); fft(Bc, q, false);
	for (int i = 0, j = 0; i < N; ++i, j = (N-1)&(N-i)) {
		T as = (Ac[i] + Ac[j].conj()) / 2;
		T al = (Ac[i] - Ac[j].conj()) / T{0, 2};
		T bs = (Bc[i] + Bc[j].conj()) / 2;
		T bl = (Bc[i] - Bc[j].conj()) / T{0, 2};
		R1[i] = as*bs + al*bl*T{0,1}, R2[i] = as*bl + al*bs;
	}
	fft(R1, q, true); fft(R2, q, true);
	ll p15 = (1LL<<15)%MOD, p30 = (1LL<<30)%MOD; C.resize(s);
	for (int i = 0; i < s; ++i) {
		ll l = llround(R1[i].u), m = llround(R2[i].u), h = llround(R1[i].v);
		C[i] = (l + m*p15 + h*p30) % MOD;
	}
}
