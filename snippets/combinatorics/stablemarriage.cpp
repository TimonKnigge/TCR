vi stable_marriage(int M, int W, vvi &mpref, vvi &wpref) {
	stack<int> st;
	for (int m = 0; m < M; ++m) st.push(m);
	vi mnext(M, 0), mmatch(M, -1), wmatch(W, -1);

	while (!st.empty()) {
		int m = st.top(); st.pop();
		if (mmatch[m] != -1) continue;
		if (mnext[m] >= W) continue;
	
		int w = mpref[m][mnext[m]++];
		if (wmatch[w] == -1) {
			mmatch[m] = w;
			wmatch[w] = m;
		} else {
			int mp = wmatch[w];
			if (wpref[w][m] < wpref[w][mp]) {
				mmatch[m] = w;
				wmatch[w] = m;
				mmatch[mp] = -1;
				st.push(mp);
			} else st.push(m);
		}
	}
	return mmatch;
}