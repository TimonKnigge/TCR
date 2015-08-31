#include "../header.h"
constexpr int SIZE = 100;
using   T = double;
using  AT = array<T,SIZE>;
using AAT = array<array<T,SIZE+1>,SIZE>;
constexpr T EPS = 1e-8;
bool mult, incost;		// true when multiple or no solutions
AT ReducedRowEchelonForm(AAT &M, int N) { // N*(N+1) matrix
	mult = false, incost = false; int r = 0;
	for(int c = 0; c < N+1 && r < N; c++) {
		int j = r;
		for(int i = r+1; i < N; i++) if(abs(M[i][c]) > abs(M[j][c])) j = i;
		if(abs(M[j][c]) < EPS) continue;
		swap(M[j], M[r]);
		auto s = 1.0 / M[r][c];
		for(int j = 0; j < N+1; j++) M[r][j] *= s;
		for(int i = 0; i < N; i++) if (i != r) {
			auto t = M[i][c];
			for(int j = 0; j < N+1; j++) M[i][j] -= t * M[r][j];
		}
		++r;
	}
	AT ans; // the back substitution phase
	for(auto j = N-1; j >= 0; --j){
		bool allzero=true; long double t=0;
		for(auto k = j+1; k < N; ++k){
			t += M[j][k] * ans[k];
			if(abs(M[j][k])>EPS) allzero=false;
		}
		if(abs(M[j][j])<EPS){
			if(allzero && abs(M[j][N]) > EPS) mult = false, incost = true;
			else mult = true;
		} else
			ans[j] = (M[j][N] - t) / M[j][j]; // the answer is here
	}
	return ans;
}
