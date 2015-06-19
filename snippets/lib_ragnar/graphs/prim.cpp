#include "../header.h"
#include "lib/adjacency_list.h"
struct Weight{int c;};
using ALG = AdjacencyListGraph<Weight,true>;
int prim(ALG& g){
	vi d(g.V, false); d[0]=true;
	int cost = 0;
	struct T{int c,v;bool operator<(T&r){return (c!=r.c) ? c > r.c : v > r.v;}};
	priority_queue<T> pq;   
	ITER(e, g.edges(0)) pq.push({e.c, e._v});
	while (!pq.empty()) {
		T cur = pq.top(); pq.pop();
		int u = cur.v, w = cur.c;
		if (!d[u]) {
			cost += cur.c; 
			d[u] = true;
			ITER(e, g.edges(u)) if (!d[e]) pq.push({e.c,e});
		}
	}                    
	return cost;
}
