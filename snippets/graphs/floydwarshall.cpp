// adj should be a V*V error s.t. adj[i][j] contains the weight of
// the edge from i to j, INF if it does not exist.
int adj[100][100];
void floyd_warshall(int V) {
	for (int b = 0; b < V; ++b)
		for (int a = 0; a < V; ++a)
			for (int c = 0; c < V; ++c)
				adj[a][c] = min(adj[a][c], adj[a][b] + adj[b][c]);
}