#include "../header.h"

// Knuth-Morris-Pratt string matching

class KMP{
	string P,T; // pattern and text
	vi jt; // jumptable for P
	int m,n;
	int i,j;
	
	KMP(){}
	KMP(const string& P):P(P){preprocess();}
	void preprocess(const string& P){
		this->P=P;
		preprocess();
	}

	void preprocess() { 
		m = P.size(); jt.resize(m+1);
		i = 0, j = -1; jt[0] = -1;
		while (i < m) {
			while (j >= 0 && P[i] != P[j]) j = jt[j];
			i++; j++;
			jt[i] = j;
		}
   	}

	void text(string T) {
		this->T=T;
		i=0,j=0;
		n = T.size();
	}

	int next(){
		while (i < n) {
			while (j >= 0 && T[i] != P[j]) j = jt[j];
			i++; j++;
			if (j == m) // match!
			{ j = jt[j]; return i;}
		}
		return -1;
   	}
};
