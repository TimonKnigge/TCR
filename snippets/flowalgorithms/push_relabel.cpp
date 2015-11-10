#include "../header.h"
#include "flowgraph.cpp"

class Push_Relabel {
public:
	FlowGraph &g; // directed
	int V, s, t; // Vertices, source and sink
	vi h, hc, qc; // height, height count, queuecount
	vector<ll> x; // excess

	Push_Relabel(FlowGraph &g, int s, int t) :
		g(g), V(g.size()), s(s), t(t), h(V,0), hc(2*V,0), qc(V,0), x(V,0){
		hc[0] = V;
	}

	int run(){
		// we initialize all heights using a BFS starting at `t`
		queue<int> q; q.push(t);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto && x : g[u])
				if(h[x.v] == 0 && x.v != t)
					hc[0]--,h[x.v] = h[u]+1,hc[h[x.v]]++, q.push(x.v);
		}

		// now set height of `s`
		hc[h[s]]--; h[s]=V; hc[V]++;

		// and push initial flows
		for(auto &&e : g[s]){
			int flow = e.cap;
			e.f = flow;
			g[e.v][e.r].f -=flow;
			x[e.v] += flow; // += for multiple edges to it
			x[s]  -= flow;
		}
		// keep a queue of overflowing vertices
		// (FIFO heuristic -> V^3)
		q = queue<int>();
		for(auto &&e : g[s])
			if(e.v!=t && qc[e.v] == 0)
				q.push(e.v), qc[e.v]=1;
		while(!q.empty()){
			int u = q.front(), m = INF;
			for(auto &&e : g[u]) if( e.cap > e.f){
				if(h[u] > h[e.v]){
					// push flow from `u` to `v`
					int flow = min(x[u], e.cap - e.f);
					e.f += flow;
					g[e.v][e.r].f -= flow;
					x[u] -= flow;
					x[e.v] += flow;

					// push overflowing `v` on queue
					if(qc[e.v] == 0 && e.v != s && e.v != t)
						qc[e.v]=1, q.push(e.v);

					if(x[u] == 0) break; // stop when done
				} else
					m = min(m, h[e.v]);
			}
			if(x[u]!=0){
				if(m!=INF){
					hc[h[u]]--;
					// apply gap heuristic
					if(hc[h[u]] == 0) // raise h[u] to V to V+1
						for(auto &&ht : h) if(ht > h[u] && ht < V)
							hc[ht]--, ht=V+1, hc[ht]++;
					h[u] = m+1;
					hc[h[u]]++;
				}
			} else qc[u]=0, q.pop();
		}
		return x[t]; // this is just the total flow
	}
};
