#include "../header.h"

template<int N>
array<double,N> GaussianElimination(array<array<double,N+1>,N> &M) {
	// input: N, Mmented Matrix M, output: Column vector X, the answer
	int i, j, k, l; double t;

	REP(i,N-1) {// eleminate rows
		l = i; // l will be the row with max value in col i
		REPI(j,i+1,N)
			if (abs(M[j][i]) > abs(M[l][i]))
				l = j;
		// swap this pivot row to minimize floating point error
		swap_ranges(M[i].begin()+i,M[i].end(),M[l].begin()+i);
		// now sweep the rows below
		REPI(j,i+1,N) REPRI(k,N+1,i)
				M[j][k] -= M[i][k] * M[j][i] / M[i][i];
	}

	array<double,N> Ans; // the back substitution phase
	REPR(j,N){
		t=0;
		REPI(k,j+1,N) t += M[j][k] * Ans[k];
		Ans[j] = (M[j][N] - t) / M[j][j]; // the answer is here
	}
	return Ans;
}
