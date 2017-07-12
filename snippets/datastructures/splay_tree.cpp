#include "../header.h"
template <typename T>
struct splay_tree {
	using node = splay_tree<T>;
	T val;
	node *l = nullptr, *r = nullptr, *p = nullptr;
	splay_tree(T _v) : val(_v) {}
	node *rotate(bool rotate_right) { // return root of rotation
		node *node::*_l, *node::*_r;
		if(rotate_right)
			_l = &node::l, _r = &node::r;
		else
			_l = &node::r, _r = &node::l;
		node *p = this, *x = p->*_l;
		assert(x);
		p->link(_l, x->*_r);
		x->link(_r, p);
		x->p = p->p;
		if(x->p) (x->p->l == p ? x->p->l : x->p->r) = x;
		return x;
	}
	node *splay() { // return new root
		node *x = this;
		if(x->isroot()) return x;
		if(x->p->isroot()) return x->p->rotate(x->isleft());
		if(x->isleft() == x->p->isleft())
			return x->p->p->rotate(isleft())->rotate(isleft())->splay();
		if(x->isright() != x->p->isleft())
			return x->p->rotate(isleft())->p->rotate(isright())->splay();
		assert(false);
	}
	void link(node *node::*_c, node *c) {
		this->*_c = c;
		if(c) c->p = this;
	}
	bool isroot() { return p == nullptr; }
	bool isleft() { return this == p->l; }
	bool isright() { return this == p->r; }
	node *max() { return r == nullptr ? this : r->max(); }
};
template <typename T>
using node = splay_tree<T>;

// adds t to the right of s; both must be roots
template <typename T>
node<T> *merge(node<T> *s, node<T> *t) {
	auto root = s->max()->splay();
	assert(root->r == nullptr);
	root->link(&node<T>::r, t);
	root->r = t;
	t->p = root;
	return root;
}

// split into [min, x) and [x, max)
template <typename T>
std::pair<node<T>, node<T>> *split(node<T> *r, node<T> *x) {
	x->splay();
	node<T> *l = x->l;
	x->l = l->p = nullptr;
	return {l, x};
}
