#include "flowgraph.cpp"
struct Dinic{
	FlowGraph& edges; int V,s,t;
	vi l; vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph& edges, int s, int t) : 
		edges(edges), V(edges.size()), s(s), t(t), l(V,-1), its(V) {}
	int augment(int u, ll c) { // we reuse the same iterators
		if (u == t) return c;
		for(auto& i = its[u]; i != edges[u].end(); i++){
			auto& e = *i;
			if (e.cap > e.f && l[u] < l[e.v]) {
				int d = augment(e.v, min(c, e.cap - e.f));
				if (d > 0) { e.f += d; edges[e.v][e.r].f -= d; return d; }
			}	}
		return 0;
	}
	int run() {
		int flow = 0, f;
		REP(u,V) its[u] = edges[u].begin();
		while(true) {
			fill(F(l),-1); l[s]=0; // recalculate the layers
			queue<int> q; q.push(s);
			while(!q.empty()){
				auto u = q.front(); q.pop();
				for(auto&& e : edges[u]) if(e.cap > e.f && l[e.v]<0)
					l[e.v] = l[u]+1, q.push(e.v);
			}
			if (l[t] < 0) return flow;
			while ((f = augment(s, INF)) > 0) flow += f;
		}	}
};
