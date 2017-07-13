#include "../header.h"
#include "./splay_tree.cpp"

template <typename T>
struct link_cut_tree : splay_tree<T, link_cut_tree<T> *> {
	using node = link_cut_tree *;
	using splay_tree_t = splay_tree<T, link_cut_tree<T> *>;
	link_cut_tree(T _v) : splay_tree_t(_v) {}

	void access(node v = nullptr) {
		// move to root
		this->splay();
		// remove preferred child
		if(this->r) {
			this->r->pp = this;
			if(v) {
				this->r->p = nullptr;
				this->r = v;
				v->pp = nullptr;
			} else
				this->unlink(&splay_tree_t::r);
		}
		if(this->pp) this->pp->access(this);
	}

	node root() {
		access();
		return up(this->min()->splay());
	}

	// cut this loose of the tree; returns the other component
	node cut() {
		access();
		node l = up(this->l);
		this->unlink(&splay_tree_t::l);
		return l;
	}

	static node up(splay_tree_t *x) { return static_cast<node>(x); }
};

template <typename T>
link_cut_tree<T> *link(link_cut_tree<T> *v, link_cut_tree<T> *w) {
	v->access();
	w->access();
	v->link(&link_cut_tree<T>::splay_tree_t::l, w);
	return v;
}

// todo: use the internal splay tree pointer for path parent
// http://codeforces.com/contest/117/submission/860934
// http://www.spoj.com/problems/DYNALCA/
