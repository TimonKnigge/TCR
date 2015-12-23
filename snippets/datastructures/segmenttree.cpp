#include "../header.h"
template <class T, T(*op)(T, T), T ident>
struct SegmentTree {
	struct Node {
		T val; int l, r;
		Node(T _val, int _l, int _r) : val(_val), l(_l), r(_r) { };
	};
	int n;
	vector<Node> tree;	// removed the 2^p nodes requirement; seems to work
	SegmentTree(vector<T> &init) : n(init.size()) {
		tree.assign(2 * n, Node(ident, 0, n - 1));
		for (int j = 1; j < n; ++j) {
			int m = (tree[j].l + tree[j].r) / 2;
			tree[2*j].l = tree[j].l;
			tree[2*j].r = m;
			tree[2*j+1].l = m + 1;
			tree[2*j+1].r = tree[j].r;
		}
		for (int j = 2 * n - 1; j > 0; --j) {
			if (j >= n) tree[j].val = init[j - n];
			else tree[j].val = op(tree[2*j].val, tree[2*j+1].val);
		}
	}
	void update(int i, T val) {
		for (tree[i+n].val = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i].val = op(tree[2*i].val, tree[2*i+1].val);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if   (l&1)  lhs = op(lhs, tree[l++].val);
			if (!(r&1)) rhs = op(tree[r--].val, rhs);
		}
		return op(l == r ? op(lhs, tree[l].val) : lhs, rhs);
	}
};
