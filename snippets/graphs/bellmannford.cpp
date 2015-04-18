// Edge list as in with Dijkstra's (see above)
bool bellmann_ford(vvii edges, int source, vi &dist) {
    dist.assign(edges.size(), INF); dist[source] = 0;
    for (int iter = 0; iter < edges.size() - 1; ++iter)
        for (int u = 0; u < edges.size(); ++u)
            for (ii e : edges[u])
                dist[e.first] = min(dist[e.first], dist[u] + e.second);
    for (int u = 0; u < edges.size(); ++u)
        for (ii e : edges[u])
            if (dist[e.first] > dist[u] + e.second)
                return false;
    return true;
}