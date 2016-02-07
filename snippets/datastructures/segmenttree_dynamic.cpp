#include "../header.h"
using T=ll; using U=ll;							// exclusive right bounds
T t_id; U u_id;
T merge(T a, T b){ return a+b; }
void join(U &a, U b){ a+=b; }
void apply(T &t, U u, int x){ t+=x*u; }
T part(T t, int range, int part){ return t/range * part; }
struct Node { int l, r, lc, rc; T t; U u;
	Node(int l, int r, T t=t_id):l(l),r(r),lc(-1),rc(-1),t(t),u(u_id){}
};
void push(Node &n, U u){ apply(n.t, u, n.r-n.l); join(n.u,u); }
struct DynamicSegmentTree {
	vector<Node> tree;
	DynamicSegmentTree(int N) { tree.push_back({0,N}); }
	T query(int l, int r, int i = 0) { auto &n = tree[i];
		if(l >= n.r || r <= n.l) return t_id;
		if(l <= n.l && n.r <= r) return n.t;
		if(n.lc < 0) return part(n.t, n.r-n.l, min(n.r,r)-max(n.l,l));
		push(tree[n.lc], n.u); push(tree[n.rc], n.u); n.u = u_id;
		return merge(query(l, r, n.lc), query(l, r, n.rc));
	}
	void update(int l, int r, U u, int i = 0) {
		auto &n = tree[i];
		if(r <= n.l || n.r <= l) return;
		if(l <= n.l && n.r <= r){ push(n,u); return; }
		if(n.lc < 0 || n.rc < 0) {
			int m = (n.l + n.r) / 2;
			n.lc = tree.size(); n.rc = tree.size()+1;
			tree.push_back({tree[i].l, m});
			tree.push_back({m, tree[i].r});
		}
		apply(tree[i].t, u, min(tree[i].r,r)-max(tree[i].l,l));
		update(l,r,u,tree[i].lc); update(l,r,u,tree[i].rc);
	}
};
