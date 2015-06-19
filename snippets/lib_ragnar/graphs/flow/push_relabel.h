#include "../smart_edge_list.h"


// Base class to use for edges
template <class E>
class Push_Relabel {
public:
	typedef SmartEdgeListGraph<E,true> G;
	typedef typename G::iterator iterator;
	G& g; // directed
	vi h, hc, e, qc; // height, height count, excess, queuecount
	int V, s,t; // Vertices, souce and sink

	Push_Relabel(G& g, int V, int s, int t) :
	   	g(g), h(V,0), hc(2*V,0), e(V,0), qc(V,0), V(V), s(s), t(t){
		hc[0] = V;
	}

	int run(){
		// we initialize all heights using a BFS starting at `t`
		queue<int> q; q.push(t); 
		while(!q.empty()){
			int u = q.front(); q.pop();
			ITER(v,g.edges(u))
				if(h[v] == 0 && v != t)
					hc[0]--,h[v] = h[u]+1,hc[h[v]]++, q.push(v);
		}
		
		// now set height of `s`
		hc[h[s]]--; h[s]=V; hc[V]++;

		// and push initial flows
		for(auto it = g.begin(s); it != g.end(s); it++){
			int flow = it->c;
			it->c = 0;
			it.reverse()->c += flow;
			e[it] += flow; // += for multiple edges to it
			e[s]  -= flow;
		}
		// keep a queue of overflowing vertices
		// (FIFO heuristic -> V^3)
		q = queue<int>();
		ITER(it, g.edges(s))
			if(it!=t && qc[it] == 0)
				q.push(it), qc[it]=1;
		while(!q.empty()){
			int u = q.front(), m = INF;
			for(auto it = g.begin(u); it != g.end(u) && e[u] > 0; it++)
				if(it->c > 0){
					if(h[u] > h[it]){
						// PUSH flow from `u` to `it`
						int flow = min(e[u], it->c);
						it->c -= flow;
						it.reverse()->c += flow;
						e[u] -= flow;
						e[it] += flow;

						// push overflowing `it` on queue
						if(qc[it] == 0 && it != s && it != t)
							qc[it]=1, q.push(it);
					} else 
						m = min(m, h[it]);
				}
			if(e[u]!=0){
				if(m!=INF){
					hc[h[u]]--;
					// apply gap heuristic
					if(hc[h[u]] == 0)
						// raise everything between h[u] and V to V+1
						REP(i,V) if(h[i] > h[u] && h[i] < V)
							hc[h[i]]--, h[i]=V+1, hc[h[i]]++;
					h[u] = m+1;
					hc[h[u]]++;
				}
			} else qc[u]=0, q.pop();
		}
		return e[t]; // this is just the total flow
	}
};
