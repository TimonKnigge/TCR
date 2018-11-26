#include "../header.h"
struct Tarjan {
	vvi &edges;
	int V, counter = 0, C = 0;
	vi n, l;
	vb vs;
	stack<int> st;
	Tarjan(vvi &e) : edges(e), V(e.size()),
		n(V, -1), l(V, -1), vs(V, false) { }
	void visit(int u, vi &com) {
		l[u] = n[u] = counter++;
		st.push(u); vs[u] = true;
		for (auto &&v : edges[u]) {
			if (n[v] == -1) visit(v, com);
			if (vs[v]) l[u] = min(l[u], l[v]);
		}
		if (l[u] == n[u]) {
			while (true) {
				int v = st.top(); st.pop(); vs[v] = false;
				com[v] = C;		//<== ACT HERE
				if (u == v) break;
			}
			C++;
		}
	}
	int find_sccs(vi &com) { // component indices will be stored in 'com'
		com.assign(V, -1);
		C = 0;
		for (int u = 0; u < V; ++u)
			if (n[u] == -1) visit(u, com);
		return C;
	}
	// scc is a map of the original vertices of the graph to the vertices
	// of the SCC graph, scc_graph is its adjacency list.
	// SCC indices and edges are stored in 'scc' and 'scc_graph'.
	void scc_collapse(vi &scc, vvi &scc_graph) {
		find_sccs(scc);
		scc_graph.assign(C,vi());
		set<ii> rec; // recorded edges
		for (int u = 0; u < V; ++u) {
			assert(scc[u] != -1);
			for (int v : edges[u]) {
				if (scc[v] == scc[u] ||
					rec.find({scc[u], scc[v]}) != rec.end()) continue;
				scc_graph[scc[u]].push_back(scc[v]);
				rec.insert({scc[u], scc[v]});
			}
		}
	}
};
