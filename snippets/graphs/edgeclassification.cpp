vvi edges;
vi color, parent;

void classify(int u) {
	color[u] = 1;
	for (int v : edges[u]) {
		if (color[v] == 0) {
			// u -> v is a tree edge
			parent[v] = u;
			classify(v);
		} else if (color[v] == 1) {
			if (v == parent[u]) {
				// u -> v, v -> u is a bidirectional edge
			} else {
				// u -> v is a back edge (thus contained in a cycle)
			}
		} else if (color[v] == 2) {
			// u -> v is a forward/cross edge
		}
	}
	color[u] = 2;
}