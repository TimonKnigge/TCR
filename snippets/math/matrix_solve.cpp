#include "../header.h"
#define REP(i, n) for(auto i = decltype(n)(0); i < (n); i++)
using T = double;
constexpr T EPS = 1e-8;
template<int R, int C>
using M = array<array<T,C>,R>;	// matrix
template<int R, int C>
T ReducedRowEchelonForm(M<R,C> &m, int rows) {	// return the determinant
	int r = 0; T det = 1;							// MODIFIES the input
	for(int c = 0; c < rows && r < rows; c++) {
		int p = r;
		for(int i=r+1; i<rows; i++) if(abs(m[i][c]) > abs(m[p][c])) p=i;
		if(abs(m[p][c]) < EPS){	det = 0; continue; }
		swap(m[p], m[r]);		det = -det;
		T s = 1.0 / m[r][c], t;	det *= m[r][c];
		REP(j,C) m[r][j] *= s;				// make leading term in row 1
		REP(i,rows) if (i!=r){ t = m[i][c]; REP(j,C) m[i][j] -= t*m[r][j]; }
		++r;
	}
	return det;
}
bool error, inconst;	// error => multiple or inconsistent
template<int R,int C>	// Mx = a; M:R*R, v:R*C => x:R*C
M<R,C> solve(const M<R,R> &m, const M<R,C> &a, int rows){
	M<R,R+C> q;
	REP(r,rows){
		REP(c,rows) q[r][c] = m[r][c];
		REP(c,C) q[r][R+c] = a[r][c];
	}
	ReducedRowEchelonForm<R,R+C>(q,rows);
	M<R,C> sol; error = false, inconst = false; 
	REP(c,C) for(auto j = rows-1; j >= 0; --j){
		T t=0; bool allzero=true;
		for(auto k = j+1; k < rows; ++k)
			t += q[j][k]*sol[k][c], allzero &= abs(q[j][k]) < EPS;
		if(abs(q[j][j]) < EPS)
			error = true, inconst |= allzero && abs(q[j][R+c]) > EPS;
		else sol[j][c] = (q[j][R+c] - t) / q[j][j]; // usually q[j][j]=1
	}
	return sol;
}

