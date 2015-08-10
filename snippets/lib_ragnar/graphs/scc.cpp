#include "../header.h"
#include "lib/adjacency_list.h"
using ALG = AdjacencyListGraph<Void,true>;
int N,M;		// nodes, edges
vi n,l;			// num, low
vb vs;			// visited?
stack<int> S;	// stack
ALG g;
int counter;	// counter
void tarjan(int u){
   	l[u]=n[u]=counter++;
	S.push(u); vs[u]=true;
	ITER(v,g.edges(u)){
		if(n[v]<0) tarjan(v);
		if(vs[v]) l[u] = min(l[u], l[v]);
	}
	if(l[u]==n[u]) // SCC found
		while(true){
			int v = S.top(); S.pop(); vs[v] = false;
			// VISIT HERE
			if(u==v)
				break;
		}
}
