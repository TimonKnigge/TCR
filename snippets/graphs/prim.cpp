typedef pair<int, ii> iii;
// Adjacency list given as (endpoint, weight)
ll prim(vvii& adj, vii& tree) {
    ll tc = 0; vb intree(adj.size(), false);
    priority_queue<iii, vector<iii>, greater<iii> > pq;
    
    intree[0] = true;
    for (ii e : adj[0]) pq.push(iii(e.second, ii(0, e.first)));
    
    while (!pq.empty()) {
        int c = pq.top().first; ii e = pq.top().second; pq.pop();
        if (intree[e.second]) continue;
        intree[e.second] = true;
        tc += c; tree.push_back(e);
        for (ii e2 : adj[e.second]) {
            if (!intree[e2.first])
                pq.push(iii(e2.second, ii(e.second, e2.first)));
        }
    }
    return tc;
}