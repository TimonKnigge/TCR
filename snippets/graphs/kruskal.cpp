#include "../header.h"
#include "../datastructures/unionfind.cpp"
// Edges are given as (weight, (u, v)) triples.
struct E {int u, v; ll weight;};
bool operator<(const E &l, const E &r){return l.weight < r.weight;}
ll kruskal(vector<E> &edges, int V) {
	sort(edges.begin(), edges.end());
	ll cost = 0, count = 0;
	UnionFind uf(V);
	for (auto &e : edges) {
		if (!uf.same(e.u, e.v)) {
			// (w, (u, v)) is part of the MST
			cost += e.weight;
			uf.union_set(e.u, e.v);
			if ((++count) == V - 1) break;
		}
	}
	return cost;
}
