#include "../header.h"
template <typename node> // argument is the derived type
struct binary_tree_node {
	using member = node *(binary_tree_node::*);
	using pr = std::pair<node *, node *>;
	node *l = nullptr, *r = nullptr, *p = nullptr;

	node *up() { return static_cast<node *>(this); }

	node *root() { return this->p ? p->root() : up(); }
	node *min() { return this->l ? l->min() : up(); }
	node *max() { return this->r ? r->max() : up(); }
	node *next() { return this->r ? this->r->min() : this->p; }
	node *prev() { return this->l ? this->l->max() : this->p; }

	bool isroot() { return p == nullptr; }
	bool isroot2() { return p == nullptr || (p->l != this && p->r != this); }
	bool isleft() { return this == p->l; }
	bool isright() { return this == p->r; }

	member get_member(bool right) {
		return right ? &binary_tree_node::r : &binary_tree_node::l;
	}
	node *child(bool right) { return this->*get_member(right); }

	node *link(member m, node *c) { // return this
		this->*m = c;
		if(c) c->p = up();
		return up();
	}
	node *link(bool right, node *c) { return link(get_member(right), c); }
	node *left(node *c) { return link(false, c); }
	node *right(node *c) { return link(true, c); }

	node *unlink(member m) { // return removed child
		node *c = this->*m;
		if(c) this->*m = c->p = nullptr;
		return c;
	}
	node *unlink(bool right) { return unlink(get_member(right)); }
	node *unleft() { return unlink(false); }
	node *unright() { return unlink(true); }
};
