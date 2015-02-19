template <class T>
class FenwickTree {
private:
	vector<T> tree;
	int n;
public:
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		while (r > 0) s += tree[r], r -= (r & (-r));
		return s;
	}
	void update(int i, T v) {
		while (i <= n) tree[i] += v, i += (i & (-i));
	}
}; 