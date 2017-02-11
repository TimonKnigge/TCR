#include "../header.h"
template <class T>
struct FenwickTree { // queries are right-exclusive; 0-based
	int n;
	vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l); } // [l,r)
	T query(int r) {                                      // [0,r)
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(++i; i <= n; i += (i & (-i))) tree[i] += v;
	}
};
