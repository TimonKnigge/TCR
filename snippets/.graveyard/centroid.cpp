#include "../header.h"
struct CentroidDecomposition {
	vvi &e;			// The original tree
	vb tocheck; 	// Used during decomposition
	vi size, p;
	int root;		// The decomposition
	vvi cd;
	CentroidDecomposition(vvi &tree) : e(tree) {
		int V = e.size();			// create initializer list?
		tocheck.assign(V, true);
		cd.assign(V, vi());
		p.assign(V, -1);
		size.assign(V, 0);

		dfs(0);
		root = decompose(0, V);
	}

	void dfs(int u) {
		for (int v : e[u]) {
			if (v == p[u]) continue;
			p[v] = u;
			dfs(v);
			size[u] += 1 + size[v];
		}
	}

	int decompose(int _u, int V) {
		// Find centroid
		int u = _u;
		while (true) {
			int nu = -1;
			for (int v : e[u]) {
				if (!tocheck[v] || v == p[u])
					continue;
				if (1 + size[v] > V / 2) nu = v;
			}
			if (V - 1 - size[u] > V / 2 && p[u] != -1
				&& tocheck[p[u]]) nu = p[u];
			if (nu != -1) u = nu; else break;
		}
		// Fix the sizes of the parents of the centroid
		for (int v = p[u]; v != -1 && tocheck[v]; v = p[v])
			size[v] -= 1 + size[u];
		// Find centroid children
		tocheck[u] = false;
		for (int v : e[u]) {
			if (!tocheck[v]) continue;
			int V2 = 1 + size[v];
			if (v == p[u]) V2 = V - 1 - size[u];
			cd[u].push_back(decompose(v, V2));
		}
		return u;
	}
};
