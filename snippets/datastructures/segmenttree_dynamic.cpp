#include "../header.h"
using T=ll; using U=ll;							// exclusive right bounds
T t_id; U u_id;
T op(T a, T b){ return a+b; }
void join(U &a, U b){ a+=b; }
void apply(T &t, U u, int x){ t+=x*u; }
T part(T t, int r, int p){ return t/r*p; }
struct DynamicSegmentTree {
	struct Node { int l, r, lc, rc; T t; U u;
		Node(int l, int r):l(l),r(r),lc(-1),rc(-1),t(t_id),u(u_id){}
	};
	vector<Node> tree;
	DynamicSegmentTree(int N) { tree.push_back({0,N}); }
	void push(Node &n, U u){ apply(n.t, u, n.r-n.l); join(n.u,u); }
	void push(Node &n){push(tree[n.lc],n.u);push(tree[n.rc],n.u);n.u=u_id;}
	T query(int l, int r, int i = 0) { auto &n = tree[i];
		if(r <= n.l || n.r <= l) return t_id;
		if(l <= n.l && n.r <= r) return n.t;
		if(n.lc < 0) return part(n.t, n.r-n.l, min(n.r,r)-max(n.l,l));
		return push(n), op(query(l,r,n.lc),query(l,r,n.rc));
	}
	void update(int l, int r, U u, int i = 0) { auto &n = tree[i];
		if(r <= n.l || n.r <= l) return;
		if(l <= n.l && n.r <= r) return push(n,u);
		if(n.lc < 0) { int m = (n.l + n.r) / 2;
			n.lc = tree.size();				n.rc = n.lc+1;
			tree.push_back({tree[i].l, m});	tree.push_back({m, tree[i].r});
		}
		push(tree[i]); update(l,r,u,tree[i].lc); update(l,r,u,tree[i].rc);
		tree[i].t = op(tree[tree[i].lc].t, tree[tree[i].rc].t);
	}
};
