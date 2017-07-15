#include "../header.h"
#include "./binary_tree_node.cpp"
#include "tcr/utils/log_scope.cpp"
template <typename node, typename T>
struct splay_tree_node : binary_tree_node<node> {
	using node_pr = std::pair<node *, node *>;
	using binary_tree_node<node>::isleft;
	T val;
	splay_tree_node(const T &t = {}) : val(t) {}
	node *up() { return static_cast<node *>(this); }
	static T *get(node *x) { return x == nullptr ? nullptr : &x->val; }
	virtual node *u() { return up(); }
	virtual node *n() { return up(); }
	node *rotate(bool right) { // return root of rotation
		node *p = up(), *x = p->child(!right);
		x->p = p->p;
		p->link(!right, x->child(right));
		x->link(right, p);
		if(x->p) (x->p->l == p ? x->p->l : x->p->r) = x;
		p->u();
		x->u();
		return x;
	}
	node *splay() { // return new root
		auto x = up();
		if(x->isroot()) return x->n();
		x->p->n();
		x->n();
		if(x->p->isroot()) return x->p->rotate(x->isleft())->n();
		bool dir;
		if((dir = x->isleft()) == x->p->isleft())
			return x->p->p->rotate(dir)->rotate(dir)->splay();
		if((dir = x->isleft()) != x->p->isleft())
			return x->p->rotate(dir)->p->rotate(!dir)->splay();
	}
	static node *merge(node *s, node *t) { // s++t, both roots
		if(s == nullptr) return t;
		return s->max()->splay()->right(t)->update();
	}
	template <typename... Ns>
	static node *merge(node *l, Ns... ns) {
		return merge(l, merge(ns...));
	}
	node_pr split() { return {splay()->unleft()->u(), up()}; }      // ..|x..
	node_pr splitleft() { return {up(), splay()->unright()->u()}; } // ..x|..
};
