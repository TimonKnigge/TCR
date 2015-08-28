#include "flowgraph.cpp"
struct Edmonds_Karp{
	FlowGraph &edges; int V,s,t; // directed graph
	Edmonds_Karp(FlowGraph &edges, int s, int t) :
		edges(edges), V(edges.size()), s(s), t(t) {}
	int run() {
		int maxflow = 0;
		bool flowfound=true;
		while (flowfound) {
			struct S{ll u, c;};
			queue<S> q; // <target, maxflow>
			vector<int> p(V,-1); // parents
			q.push({s, INF}); // s must have edges
			flowfound = false;
			while(!q.empty() && !flowfound){
				auto &f = q.front(); ll u = f.u, flow = f.c; q.pop();
				for(auto it = edges[u].begin(); it != edges[u].end(); it++)
					if(it->cap - it->f > 0 && p[it->v]==-1 && it->v != s){
						if(it->v==t){
							// augment path
							flow = min(flow, it->cap - it->f);
							while(it->v != -1){
								it->f -=flow; edges[it->v][it->r].f += flow;
								it = edges[it->v].begin() + it->r;
							}
							maxflow += flow;
							flowfound=true;
							break;
						}
						q.push({it->v, min(flow, it->cap - it->f)});
						p[it->v] = it->v;
					}
			}
		}
		return maxflow;
	}
};
