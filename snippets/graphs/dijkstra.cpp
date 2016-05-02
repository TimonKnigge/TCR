#include "../header.h"
struct Edge{ int v; ll weight; };	// input edges
struct PQ{ ll d; int v; };			// distance and target
bool operator>(const PQ &l, const PQ &r){ return l.d > r.d; }
ll dijkstra(vector<vector<Edge>> &edges, int s, int t) {
	vector<ll> dist(edges.size(),LLINF);
	priority_queue<PQ,vector<PQ>,greater<PQ>> pq;
	dist[s] = 0; pq.push({0, s});
	while (!pq.empty()) {
		auto d = pq.top().d; auto u = pq.top().v; pq.pop();
		if(u==t) break;			// target reached
		if (d == dist[u])
			for(auto &e : edges[u]) if (dist[e.v] > d + e.weight)
				pq.push({dist[e.v] = d + e.weight, e.v});
	}
	return dist[t];
}
