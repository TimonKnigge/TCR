#include "flowgraph.cpp"

// Note: Edges should be added in a single direction only
// That is: g.add_edge(u,v,{C,W},{0,-W})
// and for reverse g.add_edge(v,u,{C,W},{0,-W})
//
// We use Dijkstra's with potential to solve with
// negative edges in the residual graph
class Edmonds_Karp_Dijkstra{
public:
	FlowGraph& g; // directed
	int V,s,t;
	vector<ll> pot; // potential (distance to s)

	Edmonds_Karp_Dijkstra(FlowGraph& g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), pot(V)
	{}

	// return pair<flow, cost>
	pair<ll,ll> run() {
		ll maxflow = 0, cost = 0;
		// start by running Bellman-Ford to calculate potentials
		fill(F(pot), INF); pot[s]=0;
		REP(i,V-1) REP(u,V)
			for(auto&& e : g[u])
				if(e.cap>e.f) pot[e.v] = min(pot[e.v], pot[u] + e.cost);

		REP(i,V) cout << "dist["<<i<<"]="<<pot[i]<<"\n";
		while (true) {
			cerr << "starting new iteration\n";
			struct Q{
				int u; // target, maxflow and total weight (cost)
				ll c,w;
				bool operator<(const Q r)const{return w > r.w;}
			};
			priority_queue<Q> q;
			// edges from parent
			vector<decltype(g.front().begin())> p(V,g.front().end());
			vector<int> dist(V, INF);
			q.push({s, INF, 0}); dist[s]=0;
			ll flow;
			while(!q.empty()){
				auto& qt = q.top();
				int u = qt.u, w = qt.w,d; flow = qt.c;
				cerr << "--- u,c,w: "<<u<<","<<w<<","<<flow<<"\n";
				q.pop();
				if(w!=dist[u]) continue;
				// we visit all nodes to calculate pot
				if(u==t) break;
				for(auto&& it = g[u].begin(); it!=g[u].end(); it++){
					auto e = *it;
					d =  w + e.cost + pot[u] - pot[e.v];
					if(e.cap>e.f && d < dist[e.v]){
						q.push({e.v, min(flow, e.cap-e.f),dist[e.v] = d});
						cerr << "+++ u,c,w: "<<e.v<<","
						     <<min(flow, e.cap-e.f)<<","<<d<<"\n";
						p[e.v]=it;
					}
				}
			}
			if(p[t] == g.front().end()) return {maxflow,cost};
			// augment path
			cerr << "augmenting path with flow "<<flow<<"\n";
			auto it = p[t];
			while(it != g.front().end()){
				cerr <<it->v<<" - ";
				cost += flow * it->cost;
				it->f+=flow;
				g[it->v][it->r].f-=flow;
				it = p[g[it->v][it->r].v];
			}
			cerr << s<<"\n";
			maxflow += flow;
		}
	}
};
