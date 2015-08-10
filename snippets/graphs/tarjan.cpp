#include "../header.h"
struct Tarjan {
	vector<vi>& edges;
	int V, counter;
	vi n, l, vs;	// number, low, visited?
	stack<int> S;	// stack
	Tarjan(vector<vi>& edges) : 
		edges(edges), V(edges.size()),
		counter(0), n(V,-1), l(V, -1), vs(V,0)
	{}
	void visit(int u){
		l[u]=n[u]=counter++;
		S.push(u); vs[u] = 1;
		for(auto&& v : edges[u]) {
			if(n[v]<0) visit(v);
			if(vs[v]) l[u] = min(l[u], l[v]);
		}
		if(l[u]==n[u]) // SCC found
			while(true){
				int v = S.top(); S.pop(); vs[v] = 0;
				// <= VISIT HERE
				if(u==v)
					break;
			}
	}
	void run(){
		REP(u,V) if(vs[u] == 0) visit(u);
	}
};
