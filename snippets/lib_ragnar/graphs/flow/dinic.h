#include "../smart_edge_list.h"
#include "flowgraph.h"

class Dinic{
public:
	Graph g; int V,s,t;
	vi l; vector<size_t> its; // levels and iterators at each level

	Dinic(Graph& g, int s, int t) : 
		g(g), V(g.size()), s(s), t(t), l(V,-1), its(V) {}

	// we reuse the same iterators
	int augment(int u, ll c) {
		if (u == t) return c;
		for(auto i = its[u]; i < g[u].size(); i++){
			auto& e = g[u][i];
			if (e.cap > e.f && l[u] < l[e.v]) {
				int d = augment(e.v, min(c, e.cap - e.f));
				if (d > 0) {
					e.f += d, g[e.v][e.r].f -= d;
					return d;
				}
			}	
		}
		return 0;
	}
	int run() {
		int flow = 0, f;
		while(true) {
			fill(F(l),-1); l[s]=0; // recalculate the layers
			queue<int> q; q.push(s);
			while(!q.empty()){
				auto u = q.front(); q.pop();
				for(auto&& e : g[u])
					if(e.cap > e.f && l[e.v]<0)
						l[e.v] = l[u]+1, q.push(e.v);
			}
			if (l[t] < 0) return flow;
			fill(F(its),0);
			while ((f = augment(s, INF)) > 0)
				flow += f;
		}
	}
};
