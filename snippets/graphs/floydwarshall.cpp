#include "../header.h"
// adj should be a V*V array s.t. adj[i][j] contains the weight of
// the edge from i to j, INF if it does not exist.
// set adj[i][i] to 0; and always do adj[i][j] = min(adj[i][j], w)
int adj[100][100];
void floyd_warshall(int V) {
	for (int b = 0; b < V; ++b)
		for (int a = 0; a < V; ++a)
			for (int c = 0; c < V; ++c)
				if(adj[a][b] != INF && adj[b][c] != INF)
					adj[a][c] = min(adj[a][c], adj[a][b] + adj[b][c]);
}
void setnegcycle(int V){		// set all -Infinity distances
	REP(a,V) REP(b,V) REP(c,V)				//tested on Kattis
		if(adj[a][c] != INF && adj[c][b] != INF && adj[c][c]<0){
			adj[a][b] = - INF;
			break;
		}
}
