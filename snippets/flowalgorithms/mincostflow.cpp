#include "../header.h"
#include "flowgraph.cpp"
struct Q{ int u; ll c,w;}; // target, maxflow and total weight (cost)
bool operator>(const Q &l, const Q &r){return l.w > r.w;}
struct Edmonds_Karp_Dijkstra{
	FlowGraph &g; int V,s,t; vector<ll> pot;
	Edmonds_Karp_Dijkstra(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), pot(V) {}
	pair<ll,ll> run() { // return pair<f, cost>
		ll maxflow = 0, cost = 0;
		fill(F(pot), LLINF); pot[s]=0; // Bellman-Ford for potentials
		REP(i,V-1) {
			bool relax = false;
			REP(u,V) if(pot[u] != LLINF) for(auto &e : g[u])
				if(e.cap>e.f)
					if(pot[u] + e.cost < pot[e.v])
						pot[e.v] = pot[u] + e.cost, relax=true;
			if(!relax) break;
		}
		REP(u,V) if(pot[u] == LLINF) pot[u] = 0;
		while(true){
			priority_queue<Q,vector<Q>,greater<Q>> q;
			vector<vector<S>::iterator> p(V,g.front().end());
			vector<ll> dist(V, LLINF); ll f, tf = -1;
			q.push({s, LLINF, 0}); dist[s]=0;
			while(!q.empty()){
				auto u = q.top().u; ll w = q.top().w;
				f = q.top().c; q.pop();
				if(w!=dist[u]) continue; if(u==t && tf < 0) tf = f;
				for(auto it = g[u].begin(); it!=g[u].end(); it++){
					const auto &e = *it;
					ll d =  w + e.cost + pot[u] - pot[e.v];
					if(e.cap>e.f && d < dist[e.v]){
						q.push({e.v, min(f, e.cap-e.f),dist[e.v] = d});
						p[e.v]=it;
					}	}	}
			auto it = p[t];
			if(it == g.front().end()) return {maxflow,cost};
			maxflow += f = tf;
			while(it != g.front().end()){
				auto & r = g[it->v][it->r];
				cost += f * it->cost; it->f+=f;
				r.f -= f; it = p[r.v];
			}
			REP(u,V) if(dist[u]!=LLINF) pot[u] += dist[u];
		}
	}
};
