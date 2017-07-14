#include "../header.h"
// Edge list as in Dijkstra's (see above)
bool bellmann_ford(vvii edges, int source, vi &dist) {
	dist.assign(edges.size(), INF); dist[source] = 0;
	for (int iter = 0; iter < edges.size() - 1; ++iter){
		bool relax = false;
		for (int u = 0; u < edges.size(); ++u) {
			if (dist[u] == INF) continue;
			for (auto &e : edges[u])
				if(dist[u]+e.second < dist[e.first])
					dist[e.first] = dist[u]+e.second, relax = true;
					dist[u] + e.second);
		}
		if(!relax) break;
	}
	for (int u = 0; u < edges.size(); ++u) {
		if (dist[u] == INF) continue;
		for (auto &e : edges[u])
			if (dist[e.first] > dist[u] + e.second)
				return false;
	}
	return true;
}
