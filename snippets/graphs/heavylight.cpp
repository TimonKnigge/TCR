#include "../header.h"
struct HVL {
	int V,T; vvi &childs;	// Size; dfs-time; childs of input tree
	vi pr, size, heavy;		// path-root; size of subtrees; heavy child
	vi t_in, t_out;			// dfs in and out times
	HVL(vvi &childs) : V(childs.size()), T(0), childs(childs),
	pr(V,-1), size(V,-1), heavy(V,-1), t_in(V,-1), t_out(V,-1) {
		dfs(0); set_pr(0,-1);
	}
	int dfs(int u){
		size[u] = 1; t_in[u] = T++;
		int m = -1, mi = -1, s;		// max, max index, size of subtree
		for(auto &v : childs[u]){
			size[u] += s = dfs(v);
			if(s > m) m=s, mi = v;
		}
		heavy[u] = mi; t_out[u] = T++; return size[u];
	}
	void set_pr(int u, int r){	// node, path root
		pr[u] = r;
		for(auto &v : childs[u]) set_pr(v, heavy[u] == v ? r : v);
	}
};
