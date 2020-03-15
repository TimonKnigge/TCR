#include "../header.h"
template <class T>
struct SkewHeap {
	struct node {
		ll key, lazy = 0LL; T val;
		node *lc = nullptr, *rc = nullptr;
		node(ll k, T v) : key(k), val(v) {}
		node *prop() {
			if (lc) lc->lazy += lazy;
			if (rc) rc->lazy += lazy;
			key += lazy, lazy = 0LL;
			return this;
		}
	};
	node *r = nullptr;
	node* merge(node* x, node* y){
		if (!x) return y; else if (!y) return x;
		if (x->prop()->key > y->prop()->key) swap(x, y);
		x->rc = merge(x->rc, y);
		swap(x->lc, x->rc);
		return x;
	}
	bool empty() { return r == nullptr; }
	void insert(ll x, T val) { r = merge(r, new node(x, val)); }
	void adjust(ll c) { if (r) r->lazy += c; }
	pair<ll, T> pop_min() {
		ll w = r->prop()->key;
		T ret = r->val;
		node *nr = merge(r->lc, r->rc);
		swap(r, nr), delete nr;
		return {w, ret};
	}
	void absorb(SkewHeap<T> &o) { r = merge(r, o.r); o.r = nullptr; }
};
