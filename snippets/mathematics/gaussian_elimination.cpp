#include "../header.h"
template<int N> // solve x*M=a
array<double,N> GaussianElimination(array<array<double,N>,N> &M, array<double,N> &a) {
	REP(i,N-1) {// eleminate rows
		int l = i; // l will be the row with max value in col i
		for(auto j = i+1; j < N; ++j) // swap rows to minimize fp error
			if (abs(M[j][i]) > abs(M[l][i]))
				l = j;
		if(M[l][i]==0) continue;	// al values are already zero
		swap_ranges(M[i].begin()+i,M[i].end(),M[l].begin()+i);
		for(auto j = i+1; j < N+1; ++j){// sweep the rows below
			for(auto k = i+1; k < N; ++k)
				M[j][k] -= M[i][k] * M[j][i] / M[i][i];
			a[j] -= a[i] * M[j][i] / M[i][i];
			M[j][i] = 0;
		}
	}
	array<double,N> ans; // the back substitution phase
	for(auto j = N-1; j >= 0; --j){
		double t=0; for(auto k = j+1; k < N; ++k) t += M[j][k] * ans[k];
		ans[j] = (a[j] - t) / M[j][j]; // the answer is here
	}
	return ans;
}
