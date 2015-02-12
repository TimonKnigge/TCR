// Input is an edge list with a vector for each vertex,
// containing a list of (endpoint, weight) edges (ii's).
void dijkstra(vvii edges, int source) {
    vi dist(edges.size(), INF);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    dist[source] = 0; pq.push(ii(0, source));

    while (!pq.empty()) {
        ii top = pq.top(); pq.pop();
        int u = top.second, d = top.first;
        // <= Goal check on u here.
        if (d == dist[u]) {
            for (ii it : edges[u]) {
                int v = it.first, d_uv = it.second;
                if (dist[u] + d_uv < dist[v]) {
                    dist[v] = dist[u] + d_uv;
                    pq.push(ii(dist[v], v));
                }
            }
        }
    }
}