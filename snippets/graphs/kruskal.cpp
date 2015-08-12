#include "../header.h"
#include "../datastructures/unionfind.cpp"
// Edges are given as (weight, (u, v)) triples.
struct Edge {int u, v, weight;};
int kruskal(vector<Edge> &edges, int V) {
	sort(edges.begin(), edges.end());
	int cost = 0, count = 0;
	UnionFind uf(V);
	for (auto& e : edges) {
		if (!uf.same(e.u, e.v)) {
			// (w, (u, v)) is part of the MST
			cost += e.weight;
			uf.union_set(e.u, e.v);
			if ((++count) == V - 1) break;
		}
	}
	return cost;
}
