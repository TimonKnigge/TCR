vi sorted;
vb visited;
int s_ix = 0;
vvi edges;

void visit(int u) {
    visited[u] = true;
    for (int v : edges[u])
        if (!visited[v]) visit(v);
    sorted[s_ix--] = u;
}

void topo_sort() {
    s_ix = edges.size() - 1;
    sorted = vi(edges.size());
    visited = vb(edges.size(), false);
    for (int i = 0; i < edges.size(); ++i) {
        if (!visited[i]) visit(i);
    }
}