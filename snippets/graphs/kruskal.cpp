// Edges are given as (weight, (u, v)) triples.
int kruskal(vector< pair<int, ii> > &edges, int V) {
    sort(edges.begin(), edges.end());
    int cost = 0, count = 0;
    UnionFind uf(V);
    for (pair<int, ii> e : edges) {
        if (!uf.are_same_set(e.second.first, e.second.second)) {
            // (w, (u, v)) is part of the MST
            cost += e.first;
            uf.union_set(e.second.first, e.second.second);
            if ((++count) == V - 1) break;
        }
    }
    return cost;
}