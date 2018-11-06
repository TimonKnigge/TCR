#include "../header.h"
template <class T>
struct SkewHeap {
	struct node {
		ll key; T val;
		node *lc = nullptr, *rc = nullptr;
		node(ll k, T v) : key(k), val(v) {}
	};
	node *r = nullptr;
	node* merge(node* x, node* y){
		if (!x) return y; else if (!y) return x;
		if (x->key > y->key) swap(x, y);
		x->rc = merge(x->rc, y);
		swap(x->lc, x->rc);
		return x;
	}

	bool empty() { return r != nullptr; }
	void insert(ll x, T val) { r = merge(r, new node(x, val)); }
	T pop_min() {
		T ret = r->val;
		node *nr = merge(r->lc, r->rc);
		swap(r, nr), delete nr;
		return ret;
	}
	void absorb(SkewHeap<T> &o) { r = merge(r, o.r); o.r = nullptr; }
};
