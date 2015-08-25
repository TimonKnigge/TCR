#include "../header.h"
struct AdjEdge { int v; ll weight; };	// adjacency list edge
struct Edge { int u, v; };			// edge u->v for output
struct PQ { ll weight; Edge e; };	// PQ element
bool operator>(const PQ &l, const PQ &r) { return l.weight > r.weight; }
ll prim(vector<vector<AdjEdge>> &adj, vector<Edge> &tree) {
	ll tc = 0; vb intree(adj.size(), false);
	priority_queue<PQ, vector<PQ>, greater<PQ> > pq;
	intree[0] = true;
	for (auto &e : adj[0]) pq.push({e.weight, {0, e.v}});
	while (!pq.empty()) {
		auto &top = pq.top();
		ll c = top.weight; auto e = top.e; pq.pop();
		if (intree[e.v]) continue;
		intree[e.v] = true; tc += c; tree.push_back(e);
		for (auto &e2 : adj[e.v])
			if (!intree[e2.v]) pq.push({e2.weight, {e.v, e2.v}});
	}
	return tc;
}
