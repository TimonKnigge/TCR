#include "../smart_edge_list.h"
#include <chrono>

template <class E>
class Dinic{
public:
	typedef SmartEdgeListGraph<E,true> G;
	typedef typename G::iterator iterator;
	G& g; // directed
	int V,s,t;
	vi l; // the level of each node, l[s] = 0
	vector<iterator> its; // iterators at each level

	Dinic(G& g, int V, int s, int t) :
	   	g(g), V(V), s(s), t(t), l(V), its(V,iterator(g.end()))
	{}

	void levels(){
		// run a bfs from s in the residual graph
		// only traverse edges with positive capacity
		fill(l.begin(),l.end(), -1); l[s]=0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto it = g.begin(u); it!=g.end(u); it++)
				if(it->c > 0 && l[it]<0)
					l[it] = l[u]+1, q.push(it);
		}
	}

	// we reuse the same iterators
	int augment(int u, int c) {
		if (u == t) {return c;}
		for (auto& it = its[u] ; it!=g.end(u); it++) {
			if (it->c > 0 && l[u] < l[it]) {
				int d = augment(it, min(c, it->c));
				if (d > 0) {
					it->c -= d;
					it.reverse()->c += d;
					return d;
				}
			}
		}
		return 0;
	}

	int run() {
		int flow = 0;
		while(true) {
			levels();
			if (l[t] < 0) return flow;
			int f;
			// reinitialize iterators, ugly because of the const member in iterator
			REP(i,V) its[i].it = g.begin(i).it;
			while ((f = augment(s, INF)) > 0) {
				flow += f;
			}
		}
	}
};
