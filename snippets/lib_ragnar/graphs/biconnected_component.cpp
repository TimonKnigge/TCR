#include "../header.h"
#include "lib/adjacency_list.h"
using ALG = AdjacencyListGraph<Void,true>;
ALG g;
vi n,l,p;	// nodes,low,parent
vii bridges;
vb av;		// articulation vertices
int counter;		// num visited
int root, rchilds;	// root and root childs

void articulation_point_and_bridge(int u) {
	l[u] = n[u] = counter++;
	ITER(v,g.edges(u)) {
		if (n[v] == -1) { 
			p[v] = u; 
			if (u == root) rchilds++; 
			articulation_point_and_bridge(v);
			if (l[v] >= n[u]) av[u] = true; // articulation point
			if (l[v] > n[u])bridges.push_back({u,v});// bridge
			l[u] = min(l[u], l[v]);
		} else if (v != p[u]) // a back edge and not direct cycle
			l[u] = min(l[u], n[v]);
	}
}

// in main
void articulation_points() {
	fill(n.begin(), n.end(), -1); counter = 0;
	REP(i,g.V)
		if (n[i] == -1) {
			root = i;
			rchilds = 0;
			articulation_point_and_bridge(i);
			av[root] = (rchilds > 1); // special case
		}
}
