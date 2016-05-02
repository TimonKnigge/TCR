#include "../header.h"
void stable_marriage(vvi &mpref, vvi &wpref, vi &mmatch) {
	size_t M = mpref.size(), W = wpref.size();
	vi wmatch(W, -1);
	mmatch.assign(M, -1);
	vector<size_t> mnext(M, 0);
	stack<size_t> st;
	for (size_t m = 0; m < M; ++m) st.push(m);

	while (!st.empty()) {
		size_t m = st.top(); st.pop();
		if (mmatch[m] != -1) continue;
		if (mnext[m] >= W) continue;

		size_t w = mpref[m][mnext[m]++];
		if (wmatch[w] == -1) {
			mmatch[m] = w;
			wmatch[w] = m;
		} else {
			size_t mp = size_t(wmatch[w]);
			if (wpref[w][m] < wpref[w][mp]) {
				mmatch[m] = w;
				wmatch[w] = m;
				mmatch[mp] = -1;
				st.push(mp);
			} else	st.push(m);
		}
	}
}
