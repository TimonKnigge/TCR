#include "../header.h"
// Length only
template<class T>
int longest_increasing_subsequence(vector<T> &a) {
	set<T> st;
	typename set<T>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
	}
	return st.size();
}

// Entire sequence (indices)
template<class T>
int longest_increasing_subsequence(vector<T> &a, vector<int> &seq) {
	vector<int> lis(a.size(), 0), pre(a.size(), -1);
	int L = 0;
	for (int i = 0; i < a.size(); ++i) {
		int l = 1, r = L;
		while (l <= r) {
			int m = (l + r + 1) / 2;
			if (a[lis[m - 1]] < a[i])
				l = m + 1;
			else
				r = m - 1;
		}

		pre[i] = (l > 1 ? lis[l - 2] : -1);
		lis[l - 1] = i;
		if (l > L) L = l;
	}

	seq.assign(L, -1);
	int j = lis[L - 1];
	for (int i = L - 1; i >= 0; --i) {
		seq[i] = j;
		j = pre[j];
	}
	return L;
}
