void bellmann_ford_extended(vvii &e, int source, vi &dist, vb &cyc) {
	dist.assign(e.size(), INF);
	cyc.assign(e.size(), false);
	dist[source] = 0;
	for (int iter = 0; iter < e.size() - 1; ++iter){
		bool relax = false;
		for (int u = 0; u < e.size(); ++u)
			if (dist[u] == INF) continue;
			else for (auto &e : e[u])
				if(dist[u]+e.second < dist[e.first])
					dist[e.first] = dist[u]+e.second, relax = true;
		if(!relax) break;
	}
	bool ch = true;
	while (ch) {
		ch = false;
		for (int u = 0; u < e.size(); ++u)
			if (dist[u] == INF) continue;
			else for (auto &e : e[u])
				if (dist[e.first] > dist[u] + e.second
					&& !cyc[e.first]) {
					dist[e.first] = -INF;
					ch = true;
					cyc[e.first] = true;
				}
	}
}
