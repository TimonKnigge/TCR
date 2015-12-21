#include "../header.h"
struct HLD {
	int V; vvi &childs;
	vi &p, pr, heavy, d; // parents, path-root; heavy child, depth
	HLD(vvi &childs, vi &p, int root = 0) :
		V(p.size()), childs(childs), p(p), pr(V,-1),
		heavy(V,-1), d(V,0) {
			dfs(root); set_pr(root,0);
		}
	int dfs(int u){
		ii best; int s=1, ss;	// max, max index, size (of subtree)
		for(auto &v : childs[u])
			d[v]=d[u]+1, s+=ss=dfs(v), best = max(best,{ss,v});
		heavy[u] = best.second; return s;
	}
	void set_pr(int u, int r){		// node, path root
		pr[u] = r;
		for(auto &v : childs[u]) set_pr(v, heavy[u] == v ? r : v);
	}
	int lca(int u, int v){
		for(; pr[u]!=pr[v]; v=p[pr[u]]) if(d[pr[u]] > d[pr[v]]) swap(u,v);
		return d[u] < d[v] ? u : v;
	}
};
