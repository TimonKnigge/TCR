#include "../header.h"
#include "flowgraph.cpp"
struct Dinic{
	FlowGraph &edges; int V,s,t;
	vi l; vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t), l(V,-1), its(V) {}
	ll augment(int u, F c) { // we reuse the same iterators
		if (u == t) return c; ll r = 0LL;
		for(auto &i = its[u]; i != edges[u].end(); i++){
			auto &e = *i;
			if (e.res() && l[u] < l[e.v]) {
				auto d = augment(e.v, min(c, e.res()));
				if (d > 0) { e.f += d; edges[e.v][e.r].f -= d; c -= d;
					r += d; if (!c) break; }
		}	}
		return r;
	}
	ll run() {
		ll flow = 0, f;
		while(true) {
			fill(l.begin(), l.end(),-1); l[s]=0; // recalculate the layers
			queue<int> q; q.push(s);
			while(!q.empty()){
				auto u = q.front(); q.pop(); its[u] = edges[u].begin();
				for(auto &&e : edges[u]) if(e.res() && l[e.v]<0)
					l[e.v] = l[u]+1, q.push(e.v);
			}
			if (l[t] < 0) return flow;
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};
