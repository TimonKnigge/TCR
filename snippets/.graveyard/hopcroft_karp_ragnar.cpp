#include "../header.h"
#include "flowgraph.cpp"

class Hopcroft_Karp{
public:
	int V1; // vertices in the first part
	Graph &g;
	vi d, p; // distance (size V1), paired vertex init to INF and -1

	Hopcroft_Karp(Graph &g, int V1, int V2) : V1(V1), g(g){
		// initialize all members
		p.assign(V1+V2,-1);
		d.resize(V1); // d is assigned during bfs
	}

	// Do a BFS starting at free nodes in the first part
	// From V1 to V2, we only use unmatched edges
	// and from V2 to V1 we only use matched edges
	// this is done by going from u to p[v], where v is a neighbour of u.
	bool bfs(){
		queue<int> q; // only contains nodes in V1
		REP(v,V1) {
			if(p[v]<0) d[v]=0, q.push(v);
			else d[v]=INF;
		}
		int maxdepth = INF;
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(d[u]==maxdepth)
				return true; // paths found
			for(auto &&e : g[u]){
				if(p[e.v]==-1) // free vertex in V2
					maxdepth = d[u]+1;
				else {
					if(d[p[e.v]] < INF) continue;
					d[p[e.v]] = d[u]+1;
					q.push(p[e.v]);
				}
			}
		}
		return maxdepth != INF; // no more augmenting paths
	}

	// returns true when an augmenting path is found.
	bool dfs(int u){
		for(auto &&e : g[u])
			if(p[e.v] < 0 || d[p[e.v]]==d[u]+1)
				if(p[e.v] < 0 || dfs(p[e.v])){
					p[u]=e.v; p[e.v]=u;
					return true;
				}
		d[u]=INF; // so we don't try to reuse this vertex
		return false;
	}

	int run(){
		int matching = 0; // number of matched edges
		while(bfs())
			REP(v,V1)
				if(p[v]<0 && dfs(v)) matching++;
		return matching;
	}
};
