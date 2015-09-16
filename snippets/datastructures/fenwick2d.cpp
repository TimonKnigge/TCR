#include "../header.h"
template <class T>
struct FenwickTree2D {
	vector< vector<T> > tree;
	int n;
	FenwickTree2D(int n) : n(n) { tree.assign(n + 1, vector<T>(n + 1, 0)); }
	T query(int x1, int y1, int x2, int y2) {
		return query(x2,y2)+query(x1-1,y1-1)-query(x2,y1-1)-query(x1-1,y2);
	}
	T query(int x, int y) {
		T s = 0;
		for (int i = x; i > 0; i -= (i & (-i)))
			for (int j = y; j > 0; j -= (j & (-j)))
				s += tree[i][j];
		return s;
	}
	void update(int x, int y, T v) {
		for (int i = x; i <= n; i += (i & (-i)))
			for (int j = y; j <= n; j += (j & (-j)))
				tree[i][j] += v;
	}
};
