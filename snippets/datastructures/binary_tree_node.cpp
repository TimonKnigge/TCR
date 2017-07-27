#pragma once
#include "../header.h"
template <typename node> // argument is the derived type
struct binary_tree_node {
	using member = node *(binary_tree_node::*);
	using pr = std::pair<node *, node *>;
	node *l = nullptr, *r = nullptr, *p = nullptr;

	const node *up() const { return static_cast<const node *>(this); }
	const node *root() const { return this->p ? p->root() : up(); }

	virtual node *u() { return up(); }
	virtual node *n() { return up(); }
	node *up() { return static_cast<node *>(this); }
	node *root() { return this->p ? p->root() : up(); }
	node *min() { return this->n()->l ? l->min() : up(); }
	node *max() { return this->n()->r ? r->max() : up(); }
	node *next() {
		if(this->n()->r) return this->r->min();
		auto x = this;
		while(true) {
			if(x->isroot()) return nullptr;
			if(x->isleft()) return x->p;
			x = x->p;
		}
	}

	bool isroot() const { return p == nullptr; }
	bool isleft() const { return this == p->l; }
	bool isright() const { return this == p->r; }

	member get_member(bool right) {
		return right ? &binary_tree_node::r : &binary_tree_node::l;
	}
	node *child(bool right) { return this->*get_member(right); }

	node *link(member m, node *c) { // return this
		n();
		this->*m = c;
		if(c != nullptr) c->p = up();
		return this->u();
	}
	node *link(bool right, node *c) { return link(get_member(right), c); }
	node *left(node *c) { return link(false, c); }
	node *right(node *c) { return link(true, c); }

	node *unlink(member m) { // return removed child
		n();
		node *c = this->*m;
		if(c) this->*m = c->p = nullptr;
		this->u();
		return c;
	}
	node *unlink(bool right) { return unlink(get_member(right)); }
	node *unleft() { return unlink(false); }
	node *unright() { return unlink(true); }
};
