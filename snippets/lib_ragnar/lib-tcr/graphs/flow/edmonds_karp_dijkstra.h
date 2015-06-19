#include "../smart_edge_list.h"
#include <chrono>

// Note: Edges should be added in a single direction only
// That is: g.add_edge(u,v,{C,W},{0,-W})
// and for reverse g.add_edge(v,u,{C,W},{0,-W})
//
// We use Dijkstra's with potential to overcome 
// negative edges in the residual graph
class Edmonds_Karp_Dijkstra{
public:
	struct E{int c; int w;}; // residual capacity and weight=cost
	typedef SmartEdgeListGraph<E,true> G;
	typedef G::iterator iterator;
	G& g; // directed
	vi pi; // potential (distance to s)
	int V,s,t;

	Edmonds_Karp_Dijkstra(G& g, int V, int s, int t) :
		g(g), pi(V), V(V), s(s), t(t)
	{}

	// return pair<flow, cost>
	ii run() {
		int maxflow = 0, cost = 0;
		// start by running Bellman-Ford to calculate potentials
		fill(pi.begin(), pi.end(), INF); pi[s]=0;
		REP(i,V-1) REP(u,V) for(auto it : g.edges(u))
			if(it.c>0) pi[it] = min(pi[it], pi[u] + it.w);
		REP(i,V) cout << "dist["<<i<<"]="<<pi[i]<<"\n";
		while (true) {
			cerr << "starting new iteration\n";
			struct S{
				int u,c,w; // target, maxflow and total weight (cost)
				bool operator<(const S r)const{return w > r.w;}
			};
			priority_queue<S> q;
			vector<G::iterator> p(V,g.end()); // parents
			vector<int> dist(V, INF);
			p[s]=g.end(); q.push({s, INF, 0}); dist[s]=0;
			int flow=0;
			while(!q.empty()){
				auto& qt = q.top();
				int u = qt.u, w = qt.w,d; flow = qt.c;
				cerr << "--- u,c,w: "<<u<<","<<w<<","<<flow<<"\n";
				q.pop();
				if(w!=dist[u]) continue;
				// we visit all nodes to calculate pi
				if(u==t) break;
				for(auto it = g.begin(u); it != g.end(u); it++)
					if(it->c > 0 && (d = w+it->w + pi[u] - pi[it])<dist[it]){
						q.push({it, min(flow, it->c),dist[it] = d});
						cerr << "+++ u,c,w: "<<it<<","<<min(flow, it->c)<<","<<d<<"\n";
						p[it]= it;
					}
			}
			if(p[t] == g.end()) return {maxflow,cost};
			// augment path
			cerr << "augmenting path with flow "<<flow<<"\n";
			auto it = p[t];
			while(it != g.end()){
				cerr <<it<<" - ";
				cost += flow * it->w;
				it->c-=flow;
				it.reverse()->c+=flow;
				it = p[it.reverse()];
			}
			cerr << s<<"\n";
			maxflow += flow;
		}
	}
};
