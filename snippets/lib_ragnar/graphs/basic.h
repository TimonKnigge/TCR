#include "../header.h"
#include "adjacency_list.h"
#include "adjacency_matrix.h"
template<class T> using ALG = AdjacencyListGraph<T,true>;
template<class T> using AMG = AdjacencyMatrixGraph<T,true>;
ALG<Void> g;
vi n,p,dist; // initialize to <0 (-1)
void dfs(int u){
	n[u]=1;
	g.for_each(u,[](int v){ if(n[v]<0)dfs(v); });
}

void bfs(int s){
	queue<int> q; q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();n[u]=1;
		auto f = [&](int v){ if(n[v]<0)q.push(v); };
		g.for_each(u,f);
	}
}

void floyd_warshall(AMG<Void>& g) { // single source shortest path
	REP(k,g.V) REP(i,g.V) REP(j,g.V)
		g(i,j) = min(g(i,j),g(i,k) + g(k,j));
}
void minimax(AMG<Void>& g) { // minimal maximum edge weight
	REP(k,g.V) REP(i,g.V) REP(j,g.V)
		g(i,j) = min(g(i,j), max(g(i,k),g(k,j)));
}

void bellmann_ford(ALG<Weight>& g,int s){ // single source shortest path
	dist[s] = 0; // initialize to infinity
	REP(i,g.V) REP(u,g.V) ITER(e,g.edges(u))
		dist[e] = min(dist[e], dist[u] + e.c);
}

// run one more iteration after Bellmann-Ford
// this assumes connectedness
bool has_negative_cycle(ALG<Weight>& g) {
	bellmann_ford(g,0);
	REP(u,g.V) ITER(e,g.edges(u))
		if (dist[e] > dist[u] + e.c) return true;
	return false;
}

// reuse ALG g<Void> and n from above
vi sorted;  // visited, output
void topoVisit(int u) {
	n[u] = 1;
	ITER(v,g.edges(u)) if (n[v] == -1) topoVisit(v);
	sorted.push_back(u);
}
void topologicalSort(int N) {
	sorted.clear();
	fill(n.begin(), n.end(), -1);
	REP(i,N) if (n[i] == -1) topoVisit(i);
	reverse(sorted.begin(), sorted.end());
}

void graphCheck(int u) {		
	n[u] = 2; // in progress
	ITER(v,g.edges(u)) {
		if (n[v] == -1) // tree, white
			p[v] = u, graphCheck(v);
		else if (n[v] == 2) { // grey -> grey
			if (v == p[u]); // bidirectional 
			else; // back edge
		}
		else if (n[v] == 1){}// grey -> black,  back/cross edge
	}
	n[u] = 1; // done
}
