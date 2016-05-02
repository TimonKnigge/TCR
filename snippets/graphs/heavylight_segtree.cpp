#include "../header.h"
#include "../datastructures/segmenttree.cpp"
template <class T, T(*op)(T, T), T ident>
struct HLD { //graph may contain childs only
	int V; vvi &graph; SegmentTree<T,op,ident> st;
	vi p, r, d, h, t; // parents, path-root, depth heavy, tree index
	HLD(vvi &graph, vector<T> &init, int root = 0) :
		V(graph.size()), graph(graph), st({}),
	p(V,-1), r(V,-1), d(V,0), h(V,-1), t(V,-1){
		dfs(root); int k=0; vector<T> v(V);
		for(int i=0; i<V; ++i) if (p[i]==-1 || h[p[i]]!=i)
			for (int j=i; j!=-1; j=h[j]) r[j] = i, v[k]=init[j], t[j]=k++;
		st={v};
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
	void update(int u, ll v){ st.update(t[u],v); }
	T query(int u, int v){
		T a = ident;
		for(; r[u]!=r[v]; v=p[r[v]]){
			if(d[r[u]] > d[r[v]]) swap(u,v);
			a = op(a,st.query(t[r[v]], t[v]));
		}
		if(d[u] > d[v]) swap(u,v);
		return op(a,st.query(t[u],t[v])); // t[u]+1 if data is on edges
	}
};
