#include "../header.h"
#include "../datastructures/segmenttree.cpp"
template <class T, T(*op)(T, T), T ident>
struct HLD {
	int V,t; vi &p; vvi &childs;	// Size; dfs-time; input parent/childs
	vi pr, sz, heavy;				// path-root; subtree size; heavy child
	vi t_in, t_out, ts;				// dfs in and out times, toposort
	vi path, pi;		// only for segtree;  path number, index in path
	vector<SegmentTree<T,op,ident>> sts;
	HLD(vvi &childs, vi &p, vector<T> &init, int root = 0) :
		V(p.size()), t(0), p(p), childs(childs), pr(V,-1), sz(V,-1),
		heavy(V,-1), t_in(V,-1), t_out(V,-1), path(V,-1), pi(V,-1) {
			stack<int> s; s.push(root);		// toposort in ts (top down)
			while(!s.empty()){
				int u = s.top(); s.pop(); t_in[u] = ++t; ts.push_back(u);
				for(auto v : childs[u]) s.push(v);
			}			// use sizes of subtrees to calculate heavy edges
			for(auto it = ts.rbegin(); it!= ts.rend(); ++it){
				int u = *it; sz[u] = 1; ii m{-1,-1};
				auto &cs = childs[u];
				for(auto v : cs) sz[u] += sz[v], m = max(m,{sz[v],v});
				heavy[u] = m.second;
				t_out[u] = cs.size()>0 ? t_out[cs[0]] : t_in[u];
			}
			segtrees(init);
		}
	void segtrees(vector<T> &init){
		vector<vector<T>> pinit;					// one vector per path
		for(auto u : ts){
			if(u != 0 && u == heavy[p[u]]){
				pr[u] = pr[p[u]]; pi[u] = pi[p[u]]+1;
				path[u] = path[p[u]]; pinit[path[u]].push_back(init[u]);
			} else {
				pr[u] = u; pi[u]=0;
				path[u] = pinit.size(); pinit.push_back({init[u]});
			}
		}
		for(auto x : pinit){						// build segmenttree
			int s= 32 - __builtin_clz(x.size()-1);
			sts.push_back(SegmentTree<T,op,ident>(s, x));
		}
	}
	bool is_parent(int p, int u){	// test whether p is a parent of u
		return t_in[p] <= t_in[u] && t_out[u] <= t_out[p];
	}
	int lca(int u, int v){
		while(!is_parent(pr[v],u)) v = p[pr[v]];
		while(!is_parent(pr[u],v)) u = p[pr[u]];
		return is_parent(u,v) ? u : v;
	}
	void update(int u, T v){
		sts[path[u]].update(pi[u],v);
	}
	T query(int u, int l, bool inc){			// query up to lca
		T a = ident;
		while(path[u]!=path[l])
			a = op(a, sts[path[u]].query(0, pi[u])), u = p[pr[u]];
		return op(a, sts[path[u]].query(pi[l] + (inc ? 0 : 1), pi[u]));
	}
	T query(int u, int v){
		auto l = lca(u,v);			// include l the right number of times!
		return op(query(u,l,true), query(v,l,false));	//2x false for edges
	}
};
