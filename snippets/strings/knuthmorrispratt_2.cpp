#include "../header.h"
struct KMP{
	string P;	// pattern and text
	vi jt;		// jumptable for P
	int m;		// size of P

	KMP(const string &P):P(P){
		m = P.size(); jt.resize(m+1);
		int i = 0, j = -1; jt[0] = -1;
		while (i < m) {
			while (j >= 0 && P[i] != P[j]) j = jt[j];
			i++; j++; jt[i] = j;
		}
	}
	void match(string &T){
		int i=0, j=0;
		while (i < int(T.size())) {
			while (j >= 0 && T[i] != P[j]) j = jt[j];
			i++; j++;
			if (j == m) j = jt[j]; // match [i-m, i)
		}
	}
};
