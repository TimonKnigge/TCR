#include "../header.h"
struct HVL {
	int V;
	vi &p;			// parents
	vvi &childs;	// childs
	vi skip;		// the index of the root of the current path
	vi size;		// size of subtrees
	vi heavy;		// heavy child
	HVL(vvi &childs, vi &p) :
		V(p.size()), p(p), childs(childs),
		skip(V,-1), size(V,-1), heavy(V,-1) {
		dfs(0);		// 0 is the root
		set_skip(0,-1);
	}
	int dfs(int u){
		size[u] = 1;
		int m = -1, mi = -1, s;		// max, max index, size of subtree
		for(auto &v : childs[u]){
			size[u] += s = dfs(v);
			if(s > m) m=s, mi = v;
		}
		// make heavy edge to largest child
		heavy[u] = mi;
		return size[u];
	}
	void set_skip(int u, int pr){ // node, path root
		skip[u] = pr;
		for(auto &v : childs[u]) set_skip(v, heavy[u] == v ? pr : v);
	}
};
