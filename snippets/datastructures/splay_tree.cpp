#include "../header.h"
template <typename T, typename R> // R is kept in root nodes
struct splay_tree {
	using node = splay_tree *;
	T val;
	R pp;
	node l = nullptr, r = nullptr, p = nullptr;
	splay_tree(T _v, R _rv = {}) : val(_v), pp(_rv) {}
	node rotate(bool rotate_right) { // return root of rotation
		node splay_tree::*_l, splay_tree::*_r;
		if(rotate_right)
			_l = &splay_tree::l, _r = &splay_tree::r;
		else
			_l = &splay_tree::r, _r = &splay_tree::l;
		node p = this, x = p->*_l;
		assert(x);
		p->link(_l, x->*_r);
		x->link(_r, p);
		x->p = p->p;
		if(x->p) (x->p->l == p ? x->p->l : x->p->r) = x;

		if(x->p == nullptr) x->pp = p->pp;
		return x;
	}
	node splay() { // return new root
		node x = this;
		if(x->isroot()) return x;
		if(x->p->isroot()) return x->p->rotate(x->isleft());
		if(x->isleft() == x->p->isleft())
			return x->p->p->rotate(isleft())->rotate(isleft())->splay();
		if(x->isright() != x->p->isleft())
			return x->p->rotate(isleft())->p->rotate(isright())->splay();
		assert(false);
	}
	void link(node splay_tree::*_c, node c) {
		this->*_c = c;
		if(c) c->p = this;
	}
	void unlink(node splay_tree::*_c) {
		if(this->*_c) this->*_c = (this->*_c)->p = nullptr;
	}
	bool isroot() {
		return p == nullptr || (p->l != this && p->r != this);
	}
	bool isleft() { return this == p->l; }
	bool isright() { return this == p->r; }
	node min() { return l == nullptr ? this : l->min(); }
	node max() { return r == nullptr ? this : r->max(); }
};
template <typename T, typename R>
using node = splay_tree<T, R>;

// adds t to the right of s; both must be roots
template <typename T, typename R>
node<T, R> merge(node<T, R> s, node<T, R> t) {
	auto root = s->max()->splay();
	assert(root->r == nullptr);
	root->link(&node<T, R>::r, t);
	root->r = t;
	t->p = root;
	return root;
}

// split root r into [min, x) and [x, max)
template <typename T, typename R>
std::pair<node<T, R>, node<T, R>> *split(node<T, R> r, node<T, R> x) {
	x->splay();
	node<T, R> l = x->l;
	unlink(x, &node<T, R>::l);
	return {l, x};
}
