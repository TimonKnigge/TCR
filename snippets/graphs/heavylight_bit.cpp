#include "../header.h"
#include "../datastructures/fenwick.cpp"

struct HLD {
	vi size;		// path-root; size of subtrees; h child
	vi ts;		// dfs in and out times, toposort

	vector<FenwickTree<ll>> fts;
	// BIT stuff
	vi pi;	// index in path
	vi path;// number of the path

	int V; vvi &graph; // graph can be graph or childs only
	vi p, r, d, h; // parents, path-root; h child, depth

	HLD(vvi &graph, int root = 0) : V(graph.size()), graph(graph),
	p(V,-1), r(V,-1), d(V,0), h(V,-1) { dfs(root);
		for(int i=0; i<V; ++i) if (p[i]==-1 || h[p[i]]!=i){ // new path
			int k = 1;
			for (int j=i; j!=-1; j=h[j],++k)
				r[j] = i, path[j]=fts.size(), pi[j]=k;
			fts.push_back(FenwickTree<ll>(k));
		}
	}
	int dfs(int u){
		ii best; int s=1, ss;	// best, size (of subtree)
		for(auto &v : graph[u]) if(u!=p[v])
			d[v]=d[u]+1, p[v]=u, s += ss=dfs(v), best = max(best,{ss,v});
		h[u] = best.second; return s;
	}
	void update(int u, ll v){
		fts[path[u]].update(pi[u],v);
	}
	ll query(int u){
		if(u<0) return 0;
		return fts[path[u]].query(pi[u]) + query(p[r[u]]);
	}
	ll query(int u, int v){
		auto l = lca(u,v);
		return query(u) + query(v) - query(l) - query(p[l]);
	}
	int lca(int u, int v){
		for(; r[u]!=r[v]; v=p[r[v]]) if(d[r[u]] > d[r[v]]) swap(u,v);
		return d[u] < d[v] ? u : v;
	}
};
