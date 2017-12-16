#include "../header.h"
struct BCC{		// find AVs and bridges in an undirected graph
	vvi &edges;
	int V, counter = 0, root, rcs;		// root and # children of root
	vi n,l;								// nodes,low
	stack<int> s;
	BCC(vvi &e) : edges(e), V(e.size()), n(V,-1), l(V,-1) {}
	void visit(int u, int p) {			// also pass the parent
		l[u] = n[u] = counter++; s.push(u);
		for(auto &v : edges[u]){
			if (n[v] == -1) {
				if (u == root) rcs++; visit(v,u);
				if (l[v]>=n[u] && u!=root) {} // u is an articulation point
				if (l[v] > n[u]) {		// u<->v is a bridge
					while(true){		// biconnected component
						int w = s.top(); s.pop();	// <= ACT HERE
						if(w==v) break;
					}
				}
				l[u] = min(l[u], l[v]);
			} else if (v != p) l[u] = min(l[u], n[v]);
		}
	}
	void run() {
		for (int u = 0; u < V; ++u) if (n[u] == -1) {
			root = u; rcs = 0; visit(u,-1);
			if(rcs > 1) {}				// u is articulation point
			while(!s.empty()){			// biconnected component
				int w = s.top(); s.pop();	// <= ACT HERE
			}
		}
	}
};
