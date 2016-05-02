#include "../header.h"
struct P{ ll x,y; };
struct Box{
	ll xl, xh, yl, yh;
	Box(ll xl=-LLINF, ll xh=-LLINF, ll yl=LLINF, ll yh=LLINF) :
		xl(xl), xh(xh), yl(yl), yh(yh) {}
	bool contains(const P &p) const {
		return xl <= p.x && p.x <= xh && yl <= p.y && p.y <= yh;
	}
	bool contains(const Box &b) const {
		return xl <= b.xl && b.xh <= xh && yl <= b.yl && b.yh <= yh;
	}
	bool disjunct(const Box &b) const {
		return xh < b.xl || b.xh < xl || yh < b.yl || b.yh < yl;
	}
};
struct Node {
	ll i, cl, cr; bool hz;
	Node(ll i, bool h) : i{i}, cl{-1}, cr{-1}, hz{h} {};
};
struct KDTree {
	vector<P> &ps; vector<Node> tree;
	KDTree(vector<P> &ps) : ps{ps} {
		vi x(ps.size()); iota(x.begin(), x.end(), 0); vi y(x);
		sort(x.begin(), x.end(), [&](ll l, ll r){ return compx(l,r); });
		sort(y.begin(), y.end(), [&](ll l, ll r){ return compy(l,r); });
		tree.reserve(ps.size());
		build(x, y, true);
	}
bool compx(ll l,ll r){return tie(ps[l].x,ps[l].y,l)<tie(ps[r].x,ps[r].y,r);}
bool compy(ll l,ll r){return tie(ps[l].y,ps[l].x,l)<tie(ps[r].y,ps[r].x,r);}
	int build(vi &x, vi &y, bool h){
		if(x.size()==0) return -1;
		ll m = x.size()/2, n = tree.size();
		vi xl, xh, yl, yh;
		if(h){ // horizontal
			ll s = x[m]; tree.push_back({s, h});
			xh.assign(x.begin()+m+1, x.end()), xl = move(x);
			xl.resize(m);
			for(const auto &p : y)
				if(p==s) continue;
				else if(compx(p,s)) yl.push_back(p);
				else				yh.push_back(p);
		} else { // vertical
			ll s = y[m]; tree.push_back({s, h});
			yh.assign(y.begin()+m+1, y.end()), yl = move(y);
			yl.resize(m);
			for(const auto &p : x)
				if(p==s) continue;
				else if(compy(p,s)) xl.push_back(p);
				else				xh.push_back(p);
		}
		tree[n].cl = build(xl,yl,!h); tree[n].cr = build(xh,yh,!h);
		return n;
	}
	vi ans;		// returns a list of indices in ps
	vi query(const Box &q){ ans.clear(); query(q, Box(), 0); return ans; }
	void query(const Box &q, const Box &b, ll n){
		auto &node = tree[n]; auto &p = ps[node.i];
		if(q.contains(b)){ allq(n); return; }
		if(q.disjunct(b)) return;
		if(q.contains(p)) ans.push_back(node.i);
		Box b1=b, b2=b;
		if(node.hz) b1.xh = b2.xl = p.x;
		else		b1.yh = b2.yl = p.y;
		query(q,b1,node.cl); query(q,b2,node.cr);
	}
	void allq(ll n){ if(n==-1) return;
		ans.push_back(tree[n].i); allq(tree[n].cl); allq(tree[n].cr);
	}
};
