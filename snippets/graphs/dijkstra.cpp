#include "../header.h"
struct PQ{ int d, v; };			// distance and target
struct Edge{ int v, weight; };	// input edges
int dijkstra(vector<vector<Edge>>& edges, int s, int t) {
	vi dist(edges.size(),INF);
	priority_queue<PQ,vector<PQ>,greater<PQ>> pq;
	dist[s] = 0; pq.push({0, s});
	while (!pq.empty()) { 
		auto& top = pq.top(); pq.pop();
		auto d = top.d, u = top.v;
		if(u==t) break;			// target reached
		if (d == dist[u])
			for(auto& e : edges[u]) if (dist[e.v] > d + e.weight)
				pq.push({dist[e.v] = d + e.weight, e.v});
	}
	return dist[t];
}
