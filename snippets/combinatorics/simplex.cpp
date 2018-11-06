#include "../header.h"
#define REP(i, n) for(auto i = decltype(n)(0); i < (n); i++)
using T     = long double;
using vd    = vector<T>;
using vvd   = vector<vd>;
const T EPS = 1e-9;
struct LPSolver {
	int m, n;
	vi B, N;
	vvd D;
	LPSolver(const vvd &A, const vd &b, const vd &c)
	    : m(b.size()), n(c.size()), B(m), N(n + 1), D(m + 2, vd(n + 2)) {
		REP(i, m) REP(j, n) D[i][j] = A[i][j];
		REP(i, m) B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
		REP(j, n) N[j] = j, D[m][j] = -c[j];
		N[n]        = -1;
		D[m + 1][n] = 1;
	}
	void Pivot(int r, int s) {
		D[r][s] = 1.0 / D[r][s];
		REP(i, m + 2) if(i != r) REP(j, n + 2) if(j != s) D[i][j] -= D[r][j] * D[i][s] * D[r][s];
		REP(j, n + 2) if(j != s) D[r][j] *= D[r][s];
		REP(i, m + 2) if(i != r) D[i][s] *= -D[r][s];
		swap(B[r], N[s]);
	}
	bool Simplex(int phase) {
		int x = phase == 1 ? m + 1 : m;
		while(true) {
			int s = -1;
			REP(j, n + 1) {
				if(phase == 2 && N[j] == -1) continue;
				if(s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
			}
			if(D[x][s] >= -EPS) return true;
			int r = -1;
			REP(i, m) {
				if(D[i][s] <= EPS) continue;
				if(r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
				   (D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r]))
					r = i;
			}
			if(r == -1) return false;
			Pivot(r, s);
		}
	}
	T Solve(vd &x) {
		int r = 0;
		for(int i = 1; i < m; i++)
			if(D[i][n + 1] < D[r][n + 1]) r = i;
		if(D[r][n + 1] <= -EPS) {
			Pivot(r, n);
			if(!Simplex(1) || D[m + 1][n + 1] < -EPS) return -INF;
			REP(i, m) if(B[i] == -1) {
				int s = -1;
				REP(j, n + 1)
				if(s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
				Pivot(i, s);
			}
		}
		if(!Simplex(2)) return INF;
		x = vd(n);
		REP(i, m) if(B[i] < n) x[B[i]] = D[i][n + 1];
		return D[m][n + 1];
	}
};
