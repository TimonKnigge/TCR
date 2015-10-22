#include "../header.h"
struct Edge_Classification {
	vector<vi> &edges; int V; vi color, parent;
	Edge_Classification(vector<vi> &edges) :
		edges(edges), V(edges.size()),
		color(V,-1), parent(V, -1) {}

	void visit(int u) {
		color[u] = 1;		// in progress
		for (int v : edges[u]) {
			if (color[v] == -1) { // u -> v is a tree edge
				parent[v] = u;
				visit(v);
			} else if (color[v] == 1) {
				if (v == parent[u]) {} // u -> v is a bidirectional edge
				else {} // u -> v is a back edge (thus contained in a cycle)
			} else if (color[v] == 2) {} // u -> v is a forward/cross edge
		}
		color[u] = 2;		// done
	}
	void run(){
		for (int u = 0; u < V; ++u) if(color[u] < 0) visit(u);
	}
};
