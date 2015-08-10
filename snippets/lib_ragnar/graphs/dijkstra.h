#include "../header.h"
#include "../graphs/adjacency_list.h"

struct S{
	int d, v; // distance and target
	bool operator<(S r){return d > r.d;}
}; 
typedef AdjacencyListGraph<Weight,true> ALG;
int dijkstra(ALG& g, int s, int t) {
	vi dist(g.V,INF);
	priority_queue<S> pq;
	pq.push({0, s}); dist[s] = 0;
	while (!pq.empty()) { 
		S c = pq.top(); pq.pop();
		int d = c.d, u = c.v;
		if(u==t){break;} // target reached
		if (d == dist[u]){
			ITER(v,g.edges(u)) {
				if (dist[v] > d + v.c) {
					dist[v] = d + v.c; 
					pq.push({dist[v], v}); 
	}	}	}	}
	return dist[t];
}

