#include "../header.h"
#include "./binary_tree_node.cpp"
template <typename node, typename T>
struct splay_tree_node : binary_tree_node<node> {
	using node_pr = std::pair<node *, node *>;
	using binary_tree_node<node>::isleft;
	T val;
	splay_tree_node(const T &t = {}) : val(t) {}
	static T *get(node *x) { return x == nullptr ? nullptr : &x->val; }
	virtual node *u() { return this->up(); }
	virtual node *n() { return this->up(); }
	node *rotate(bool right) { // return root of rotation
		node *p = this->up(), *x = p->child(!right);
		x->p = p->p;
		p->link(!right, x->child(right));
		x->link(right, p);
		if(x->p) (x->p->l == p ? x->p->l : x->p->r) = x;
		p->u();
		x->u();
		return x;
	}
	node *splay() { // return new root
		auto x = this->up();
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
		return s->max()->splay()->right(t)->u();
	}
	template <typename... Ns>
	static node *merge(node *l, Ns... ns) {
		return merge(l, merge(ns...));
	}
	node_pr split(bool right = true) {
		return right ? node_pr{splay()->unleft(), this->up()}
		             : node_pr{this->up(), splay()->unright()};
	}
};
