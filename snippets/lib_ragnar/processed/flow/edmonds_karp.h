#include "../smart_edge_list.h"
#include <chrono>

class Edmonds_Karp{
public:
	struct E{int c;}; // residual capacity
	typedef SmartEdgeListGraph<E,true> G;
	typedef G::iterator iterator;
	G& g; // directed
	int V,s,t;

	Edmonds_Karp(G& g, int V, int s, int t) :
		g(g), V(V), s(s), t(t)
	{}

	int run() {
		int maxflow = 0;
		bool flowfound=true;
		while (flowfound) {
			struct S{int u, c;};
			queue<S> q; // <target, maxflow>
			vector<G::iterator> p(V,g.end()); // parents
			p[s]=g.end();
			// push all edges from s with their capacity
			q.push({s, INF}); // s must have edges
			flowfound = false;
			while(!q.empty() && !flowfound){
				auto& f = q.front(); int u = f.u; int flow = f.c; q.pop();
				for(auto it = g.begin(u); it != g.end(u); it++)
					if(it->c > 0 && p[it]==g.end() && it != s){
						if(it==t){
							// augment path
							flow = min(flow, it->c);
							while(it != g.end()){
								it->c-=flow; it.reverse()->c+=flow;
								it = p[it.reverse()];
							}
							maxflow += flow;
							flowfound=true;
							break;
						}
						q.push({it, min(flow, it->c)});
						p[it] = it;
					}
			}
		}
		return maxflow;
	}
};
