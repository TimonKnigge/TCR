#include "../header.h"
#include "flowgraph.cpp"
struct Edmonds_Karp{
	FlowGraph &g; int V,s,t; // directed graph
	Edmonds_Karp(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t) {}
	ll run() {
		ll maxf = 0;
		while (true) {
			struct T{int u; ll f;}; queue<T> q;
			auto end = g[0].end(); vector<vector<S>::iterator> p(V,end);
			q.push({s, LLINF}); ll f;
			while(!q.empty()){
				auto u = q.front().u; f = q.front().f; q.pop();
				for(auto it = g[u].begin(); it != g[u].end(); ++it){
					const auto &e = *it;
					if(e.cap > e.f && p[e.v]==end && e.v != s){
						p[e.v] = it; q.push({e.v, min(f, e.cap - e.f)});
						if(e.v == t){ f = min(f, e.cap - e.f); goto end;}
			}	}	}
end:		auto it = p[t]; if(it == end) return maxf;
			while(it != end){
				auto &r = g[it->v][it->r];
				it->f += f; r.f -= f; it = p[r.v];
			}
			maxf += f;
	}	}
};
