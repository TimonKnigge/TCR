#include "../header.h"
using T = double;						// type
template<int R, int C>
using M = array<array<T,C>,R>;	// matrix
constexpr T EPS = 1e-8;
template<int R, int C>
void ReducedRowEchelonForm(M<R,C> &m) {
	int r = 0;
	for(int c = 0; c < C && r < R; c++) {
		int j = r;
		for(int i = r+1; i < R; i++) if(abs(m[i][c]) > abs(m[j][c])) j = i;
		if(abs(m[j][c]) < EPS) continue;
		swap(m[j], m[r]);
		auto s = 1.0 / m[r][c];
		REP(j,C) m[r][j] *= s;
		REP(i,R) if (i != r) REP(j,C) m[i][j] -= m[i][c] * m[r][j];
		++r;
	}
}

bool error, inconst;	// error => multiple or inconsistent
template<int R, int C>	// Mx = a; M:R*R, v:R*C => x:R*C
M<R,C> solve(const M<R,R> &m, const M<R,C> &a){
	M<R,R+C> q;
	REP(r,R){
		REP(c,R) q[r][c] = m[r][c];
		REP(c,R) q[r][R+c] = a[r][c];
	}
	ReducedRowEchelonForm(q);
	M<R,C> sol; error = false, inconst = false; 
	REP(c,C) for(auto j = R-1; j >= 0; --j){
		T t=0; bool allzero=true;
		for(auto k = j+1; k < R; ++k)
			t += q[j][k]*sol[k][c], allzero &= abs(q[j][k]) < EPS;
		if(abs(q[j][j]) < EPS)
			error = true, inconst |= allzero && abs(q[j][R+c]) > EPS;
		else sol[j][c] = (q[j][R+c] - t) / q[j][j];
	}
	return sol;
}
