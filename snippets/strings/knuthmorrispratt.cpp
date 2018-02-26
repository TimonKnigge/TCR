#include "../header.h"
void compute_prefix_function(string &w, vi &pi) {
	pi.assign(w.length(), 0);
	int k = pi[0] = -1;

	for(int i = 1; i < w.length(); ++i) {
		while(k >= 0 && w[k + 1] != w[i]) k = pi[k];
		if(w[k + 1] == w[i]) k++;
		pi[i] = k;
	}
}

void knuth_morris_pratt(string &s, string &w) {
	int q = -1;
	vi pi;
	compute_prefix_function(w, pi);
	for(int i = 0; i < s.length(); ++i) {
		while(q >= 0 && w[q + 1] != s[i]) q = pi[q];
		if(w[q + 1] == s[i]) q++;
		if(q + 1 == w.length()) {
			// Match at position (i - w.length() + 1)
			q = pi[q];
		}
	}
}
