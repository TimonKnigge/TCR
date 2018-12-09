#include "../header.h"
#include "./dinic.cpp"
struct edge { int u, v; ll w; };
struct GomoryHuTree {		// After construction, for all n-1 i such that
	int V; vi p, w, c;		// p[i] \geq 0, the edge (i, p[i]) is in the GH
	vector<edge> tree;		// tree with weight w[i].
	void dfs(int u, const FlowGraph &fg) {
		c[u] = 1;
		for (const auto &e : fg[u]) if (!c[e.v] && e.res()) dfs(e.v, fg);
	}
	GomoryHuTree(int n, const vector<edge> &E) : V(n), p(V), w(V), c(V) {
		FlowGraph fg(V);
		for (const edge &e : E) fg.add_edge(e.u, e.v, e.w);
		p[0] = -1, std::fill(p.begin() + 1, p.end(), 0);
		for (int i = 1; i < V; ++i, fg.clear()) {
			w[i] = Dinic(fg, i, p[i]).run();
			std::fill(c.begin(), c.end(), 0);
			dfs(i, fg);
			for (int j = i+1; j < V; ++j)
				if (c[j] && p[j] == p[i]) p[j] = i;
			if (p[p[i]] >= 0 && c[p[p[i]]]) {
				int pi = p[i];
				swap(w[i], w[pi]);
				p[i] = p[pi], p[pi] = i;
			}
		}
	}
};
