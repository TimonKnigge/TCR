#include "../header.h"
#include "../datastructures/fenwick.cpp"

/*
 *	This currently contains code for 2 possible implementations:
 *	1) keep a FenwickTree per path, and use indices of each
 *		vertex to keep track of path and index in path
 *	2) store the data directly in the graph,
 *		and create next[u] and prev[u] pointers
 *
 *	Option 1 is about twice as fast for updates on large graphs
 */

struct HLD {
	int V,T; vi &p; vvi &childs;	// Size; dfs-time; input parent/childs
	vi pr, size, heavy;		// path-root; size of subtrees; heavy child
	vi t_in, t_out, ts;		// dfs in and out times, toposort

	// using separate Fenwick Tree
	vector<FenwickTree<ll>> fts;
	vi pi; // BIT stuff
	vi path;

	// using paths within HLD
	//vector<ll> vals; vi next, prev;
	HLD(vvi &childs, vi &p, int root = 0) :
		V(p.size()), T(0), p(p), childs(childs), pr(V,-1), size(V,-1),
		heavy(V,-1), t_in(V,-1), t_out(V,-1), pi(V,-1), path(V,-1)
		//vals(V,0), next(V,-1), prev(V,-1) 
		{
			tsort(root); set_sizes(); set_fts();
		}
	void tsort(int r){
		stack<int> s; s.push(r);
		while(!s.empty()){
			int u = s.top(); s.pop(); t_in[u] = ++T; ts.push_back(u);
			for(auto v : childs[u]) s.push(v);
		}
	}
	void set_sizes(){
		vi s(V,0);
		for(auto it = ts.rbegin(); it!= ts.rend(); ++it){
			int u = *it; s[u] = 1;
			pair<int,int> m{-1,-1};
			auto &cs = childs[u];
			for(auto v : cs) s[u] += s[v], m = max(m,{s[v],v});
			heavy[u] = m.second; t_out[u] = cs.size() > 0 ? t_out[cs[0]] : t_in[u];
		}
	}
	void set_fts(){
		for(auto u : ts){
			int i;
			if(u != 0 && u == heavy[p[u]])
				pr[u] = pr[p[u]], pi[u] = pi[p[u]]+1, i = path[p[u]];
			else
				pr[u] = u, pi[u]=1, i = fts.size(), fts.push_back(FenwickTree<ll>(0));
			path[u] = i;
			fts[i].tree.push_back(0);
		}
		for(auto &x : fts) x.n = x.tree.size() - 1;
		Log("calculating prev,next");
		/*
		for(int u = 0; u < V; ++u){
			int i = pi[u];
			// prev
			int v = u;
			if(i!=(i&-i)) for(int k=0; v>=0 && k<(i&-i); ++k) v=p[v];
			else v = -1;
			prev[u]=v;
			v = u;
			for(int k=0; v>=0 && k<(i&-i); ++k) v=heavy[v];
			next[u]=v;
			Log(u,prev[u],next[u]);
		}
		*/
	}
	bool is_parent(int p, int u){	// test whether p is a parent of u
		return t_in[p] <= t_in[u] && t_out[p] >= t_out[u];
	}
	int lca(int u, int v){
		while(!is_parent(pr[v],u)) v = p[pr[v]];
		while(!is_parent(pr[u],v)) u = p[pr[u]];
		return is_parent(u,v) ? u : v;
	}
	void update(int u, ll v){
		fts[path[u]].update(pi[u],v);
		//while(u>=0) vals[u]+=v, u=next[u];
	}
	ll query(int u){
		if(u<0) return 0;
		//ll ans = 0;
		//int v = u;
		//while(v>=0) ans += vals[v], v=prev[v];
		//return ans + query(p[pr[u]]);
		return fts[path[u]].query(pi[u]) + query(p[pr[u]]);
	}
	ll query(int u, int v){
		auto l = lca(u,v);
		return query(u) + query(v) - query(l) - query(p[l]);
	}
};
