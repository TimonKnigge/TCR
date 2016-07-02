
struct AdvancedUnionFind {
	int n, c;
	bool bipartite = true;
	resettable_vector<int> par, rank, size;
	resettable_vector<bool> sign;
	
	AdvancedUnionFind(int _n) : n(_n), c(n), par(n, 0),
		rank(n, 0), size(n, 1), sign(n, false) {
		for (int i = 0; i < n; ++i)
			par.set(i, i), par.set_default(i, i);
	}
	int find(int i) {
		if (par.get(i) == i) return i;
		int p = find(par.get(i));
		if (par.get(i) != p && sign.get(par.get(i)))
			sign.set(i, !sign.get(i));
		par.set(i, p);
		return p;
	}
	bool same(int i, int j) { return find(i) == find(j); }
	bool sign_of(int u, int pu = -1) {
		if (pu == -1) pu = find(u);
		bool su = sign.get(u);
		if (u != pu && sign.get(pu)) su = !su;
		return su;
	}
	void add_edge(int i, int j, bool diff = true) {
		int pi = find(i), pj = find(j);
		if (pi == pj) {
			bool si = sign_of(i, pi), sj = sign_of(j, pj);
			if (si == sj && diff) bipartite = false;
			if (si != sj && !diff) bipartite = false;
		}
		c--;
		if (rank.get(pi) > rank.get(pj)) swap(i, j), swap(pi, pj);
		bool si = sign_of(i, pi), sj = sign_of(j, pj);
		if ((si == sj && diff) || (si != sj && !diff))
			sign.set(pi, !sign.get(pi));
		par.set(pi, pj); size.set(pj, size.get(pj) + size.get(pi));
		if (rank.get(pi) == rank.get(pj)) rank.set(pj, rank.get(pj)+1);
	}
	void reset() {
		par.reset();
		rank.reset();
		size.reset();
		sign.reset();
		bipartite = true;
		c = n;
	}
};
