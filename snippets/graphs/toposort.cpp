#include "../header.h"
struct Toposort {
	vector<vi> &edges;
	int V, s_ix; // sorted-index
	vi sorted, visited;

	Toposort(vector<vi> &edges) :
		edges(edges), V(edges.size()), s_ix(V),
		sorted(V,-1), visited(V,false) {}

	void visit(int u) {
		visited[u] = true;
		for (int v : edges[u])
			if (!visited[v]) visit(v);
		sorted[--s_ix] = u;
	}
	void topo_sort() {
		for (int i = 0; i < V; ++i) if (!visited[i]) visit(i);
	}
};
