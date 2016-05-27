#include "../header.h"
// All points should be within [-B, B] x [-B, B]
// CAP is an UB on the projected number of nodes
ii def = {LLINF, LLINF};
template <ll B, int CAP>
struct QuadTree {
	struct node {
		int ch = -1, pc = 0;
		ll x1, y1, x2, y2;
		ii pt = def;
	};
	vector<node> tree;
	int T = 0;
	QuadTree() { tree.assign(CAP, node()); make_node(-B, -B, B, B); }
	int make_node(ll x1, ll y1, ll x2, ll y2) {
		tree[T].x1 = x1; tree[T].y1 = y1;
		tree[T].x2 = x2; tree[T].y2 = y2;
		return T++;
	}
	void insert(ii pt, int w = 1, int n = 0) {
		node &nd = tree[n];
		if ((nd.ch < 0 && nd.pt == def) || nd.pt == pt) {
			nd.pt = pt;
			nd.pc += w;
			return;
		}
		int xm = (nd.x1+nd.x2) / 2, ym = (nd.y1+nd.y2) / 2;
		if (nd.pt != def) {
			nd.ch = make_node(nd.x1, nd.y1, xm,    ym);
			make_node(xm+1,  nd.y1, nd.x2, ym);
			make_node(nd.x1, ym+1,  xm,    nd.y2);
			make_node(xm+1,  ym+1,  nd.x2, nd.y2);
			insert_child(nd.pt, nd.pc, n);
			nd.pt = def;
		}
		insert_child(pt, w, n); nd.pc = 0;
		for (int i = 0; i < 4; ++i) nd.pc += tree[nd.ch + i].pc;
	}
	void insert_child(ii pt, int w, int n) {
		node &nd = tree[n];
		if (pt.first <= (nd.x1+nd.x2) / 2)
			if (pt.second <= (nd.y1+nd.y2) / 2)
				insert(pt, w, nd.ch);
			else	insert(pt, w, nd.ch + 2);
		else	if (pt.second <= (nd.y1+nd.y2) / 2)
				insert(pt, w, nd.ch + 1);
			else	insert(pt, w, nd.ch + 3);
	}
	int query(ll x1, ll y1, ll x2, ll y2, int n = 0) {
		node &nd = tree[n];
		if (x1 <= nd.x1 && y1 <= nd.y1 && nd.x2 <= x2 && nd.y2 <= y2)
			return nd.pc;
		if (nd.x2 < x1 || x2 < nd.x1 || nd.y2 < y1 || y2 < nd.y1)
			return 0LL;
		ll ret = 0LL;
		if (nd.ch >= 0)
			for (int i = 0; i < 4; ++i)
				ret += query(x1, y1, x2, y2, nd.ch + i);
		else if (nd.pt != def)
			if (x1 <= nd.pt.first && nd.pt.first <= x2
			 && y1 <= nd.pt.second && nd.pt.second <= y2)
				ret += nd.pc;
		return ret;
	}
};
