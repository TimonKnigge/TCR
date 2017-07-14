#include "../header.h"
#include "../datastructures/fenwick.cpp"
struct HLD {
	int V; vvi &graph; FenwickTree<ll> ft; //graph may contain childs only
	vi p, r, d, h, t; // parents, path-root; heavy, tree index
	HLD(vvi &graph, int root = 0) : V(graph.size()), graph(graph), ft(V),
	p(V,-1), r(V,-1), d(V,0), h(V,-1), t(V,-1){
		dfs(root); int k=0;
		for(int i=0; i<V; ++i) if (p[i]==-1 || h[p[i]]!=i)
			for (int j=i; j!=-1; j=h[j]) r[j] = i, t[j]=++k;
	}
	int dfs(int u){
		ii best={-1,-1}; int s=1, ss;	// best, size (of subtree)
		for(auto &v : graph[u]) if(v!=p[u])
			d[v]=d[u]+1, p[v]=u, s += ss=dfs(v), best = max(best,{ss,v});
		h[u] = best.second; return s;
	}
	int lca(int u, int v){
		for(; r[u]!=r[v]; v=p[r[v]]) if(d[r[u]] > d[r[v]]) swap(u,v);
		return d[u] < d[v] ? u : v;
	}
	void update(int u, ll v){ ft.update(t[u],v); }
	ll query(int u, int v){
		ll a = 0;
		for(; r[u]!=r[v]; v=p[r[v]]){
			if(d[r[u]] > d[r[v]]) swap(u,v);
			a += ft.query(t[r[v]], t[v]);
		}
		if(d[u] > d[v]) swap(u,v);
		return a + ft.query(t[u],t[v]);
	}
};
