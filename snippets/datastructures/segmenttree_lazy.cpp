#include "../header.h"
using T=int; using U=int;
T t_id; U u_id;
T merge(T a, T b){return a+b;}
void join(U &a, U b){ a=a+b; }
T apply(T t, U u, int n){ return merge(t, n*u); }
struct LazySegmentTree {
	struct Node {
		int l, r, lc, rc; T t; U u;
		Node(int l, int r) : l(l), r(r), lc(-1), rc(-1), t(t_id), u(u_id) {}
	};
	vector<Node> tree;
	void build(int i, int l, int r, const vector<T> &arr) {
		auto &n = tree[i];
		if (l < r) {
			int m = (l + r) / 2;
			n.lc = tree.size();		n.rc = tree.size()+1;
			tree.push_back({l,m});	tree.push_back({m+1,r});
			build(n.lc,l,m,arr);	build(n.rc,m+1,r,arr);
			n.t = merge(tree[n.lc].t, tree[n.rc].t);
		} else n.t = arr[l];
	}
	LazySegmentTree(const vector<T> &arr){
		tree.reserve(2*arr.size()-1);
		tree.push_back({0,int(arr.size())-1});
		build(0, 0, arr.size()-1, arr);
	}
	T query(int l, int r, int i = 0) {	// 0 <= l <= r < n
		auto &n = tree[i];
		if(l > n.r || r < n.l) return t_id;
		if(l <= n.l && n.r <= r) return apply(n.t,n.u, n.r-n.l+1);
		n.t = apply(n.t, n.u, n.r-n.l+1);
		join(tree[n.lc].u, n.u); join(tree[n.rc].u, n.u);
		n.u = u_id;
		return merge(query(l,r,n.lc),query(l,r,n.rc));
	}
	void update(int l, int r, U u, int i = 0) {
		auto &n = tree[i];
		if(l > n.r || r < n.l) return;
		if(l <= n.l && n.r <= r){ join(n.u,u); return; }
		update(l,r,u,n.lc); update(l,r,u,n.rc);		// push update
		auto& lc = tree[n.lc], &rc=tree[n.rc];
		auto m1 = apply(lc.t, lc.u, lc.r - lc.l + 1);
		auto m2 = apply(rc.t, rc.u, rc.r - rc.l + 1);
		n.t = merge(m1,m2);
	}
};
