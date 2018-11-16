#include "../header.h"
#include "flowgraph.cpp"
using F = ll; using W = ll; W WINF = LLINF; F FINF = LLINF;
struct Q{ int u; F c; W w;}; // target, maxflow and total cost/weight
bool operator>(const Q &l, const Q &r){return l.w > r.w;}
struct Edmonds_Karp_Dijkstra{
	FlowGraph &g; int V,s,t; vector<W> pot;
	Edmonds_Karp_Dijkstra(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), pot(V) {}
	pair<F,W> run() { // return pair<f, cost>
		F maxflow = 0; W cost = 0;			// Bellmann-Ford for potentials
		fill(pot.begin(),pot.end(),WINF); pot[s]=0;
		for (int i = 0; i < V - 1; ++i) {
			bool relax = false;
			for (int u = 0; u < V; ++u) if(pot[u] != WINF)
				for(auto &e : g[u])
					if(e.cap>e.f)
						if(pot[u] + e.cost < pot[e.v])
							pot[e.v] = pot[u] + e.cost, relax=true;
			if(!relax) break;
		}
		for (int u = 0; u < V; ++u) if(pot[u] == WINF) pot[u] = 0;
		while(true){
			priority_queue<Q,vector<Q>,greater<Q>> q;
			vector<vector<S>::iterator> p(V,g.front().end());
			vector<W> dist(V, WINF); F f, tf = -1;
			q.push({s, FINF, 0}); dist[s]=0;
			while(!q.empty()){
				int u = q.top().u; W w = q.top().w;
				f = q.top().c; q.pop();
				if(w!=dist[u]) continue; if(u==t && tf < 0) tf = f;
				for(auto it = g[u].begin(); it!=g[u].end(); it++){
					auto &e = *it;
					W d =  w + e.cost + pot[u] - pot[e.v];
					if(e.cap>e.f && d < dist[e.v]){
						q.push({e.v, min(f, e.cap-e.f),dist[e.v] = d});
						p[e.v]=it;
					}	}	}
			auto it = p[t];
			if(it == g.front().end()) return {maxflow,cost};
			maxflow += f = tf;
			while(it != g.front().end()){
				auto &r = g[it->v][it->r];
				cost += f * it->cost; it->f+=f;
				r.f -= f; it = p[r.v];
			}
			for (int u = 0; u < V; ++u) if(dist[u]!=WINF) pot[u] += dist[u];
		}
	}
};
