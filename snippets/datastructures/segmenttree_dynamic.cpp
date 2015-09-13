#include "../header.h"
using T=int; using U=int;
T t_id; U u_id;
T merge(T a, T b){ return a+b; }
void join(U &a, U b){ a=a+b; }
T apply(T t, U u, int n){ return merge(t,n*u); }
pair<T,T> split(T t, ll a, ll b){ return {t/(a+b)*a, t/(a+b)*b}; }
struct DynamicSegmentTree {
	struct Node {
		int l, r, lc, rc; T t; U u;
		Node(int l, int r, T t=t_id):l(l),r(r),lc(-1),rc(-1),t(t),u(u_id){}
	};
	vector<Node> tree;
	DynamicSegmentTree(int N) { tree.push_back({0,N-1}); }
	T query(int l, int r, int i = 0) {			// 0 <= l <= r < n
		auto &n = tree[i];
		if(l > n.r || r < n.l)	 return t_id;	// <- disjunct, vv internal
		if(l <= n.l && n.r <= r) return apply(n.t, n.u, n.r-n.l+1);
		if(n.lc < 0 || n.rc < 0)				// unexpanded node
			return apply(n.t, n.u, min(n.r,r) - max(n.l,l) + 1);
		n.t = apply(n.t, n.u, n.r-n.l+1);
		join(tree[n.lc].u, n.u);				// push the update
		join(tree[n.rc].u, n.u); n.u = u_id;	// and reset the update
		return merge(query(l, r, n.lc), query(l, r, n.rc));
	}
	void update(int l, int r, U u, int i = 0) {
		auto &n = tree[i];
		if(l > n.r || r < n.l) return;
		if(l <= n.l && n.r <= r){ join(n.u,u); return; }
		if(n.lc < 0 || n.rc < 0) {
			int m = (n.l + n.r) / 2;
			n.lc = tree.size(); n.rc = tree.size()+1;
			auto sp = split(n.t,m-n.l+1,n.r-m);
			tree.push_back({tree[i].l,  m, sp.first});
			tree.push_back({m+1,tree[i].r, sp.second});
		}		// DON'T use `n` anymore, because tree may reallocate
		update(l,r,u,tree[i].lc);
		update(l,r,u,tree[i].rc);
		auto& lc = tree[tree[i].lc], &rc=tree[tree[i].rc];
		auto m1 = apply(lc.t, lc.u,lc.r-lc.l+1);
		auto m2 = apply(rc.t, rc.u,rc.r-rc.l+1);
		tree[i].t = merge(m1,m2);
	}
};
