#include "../header.h"
#include "./binary_tree_node.cpp"
template <typename node, typename T>
struct seq : binary_tree_node<node> {
	using np = pair<node *, node *>;
	T val;
	int priority;
	seq(T _v = {}) : val(_v) { priority = rand(); }
	virtual node *u() { return this->up(); } // override for update
	virtual node *n() { return this->up(); } // override for normalize
	node *update() {
		if(this->l) this->l->p = this->up();
		if(this->r) this->r->p = this->up();
		return u();
	}
	np split(bool right = true) {
		auto _l = this->get_member(!right), _r = this->get_member(right);
		node *A = this->up();
		if(A == nullptr) return {nullptr, nullptr};
		node *B = A, *lr = A;
		A = A->*_l;
		if(A == nullptr && lr->p == nullptr) {
			return right ? np{nullptr, B} : np{B, nullptr};
		}
		if(A == nullptr) {
			while(lr->p && lr->p->*_l == B) lr = B = lr->p;
			if(lr->p) {
				lr = A = lr->p;
				lr->unlink(right);
			}
		} else
			lr->unlink(!right);
		while(lr->update()->p) {
			if(lr->p->*_l == lr) {
				if(lr == A) swap(A->p, B->p), B->p->*_l = B;
				lr = B = B->p;
			} else {
				if(lr == B) swap(A->p, B->p), A->p->*_r = A;
				lr = A = A->p;
			}
		}
		return right ? np{A, B} : np{B, A};
	}
	// Note: Assumes both nodes are the roots of their sequences.
	static node *merge(node *A, node *B) {
		if(A == nullptr) return B;
		if(B == nullptr) return A;
		if(A->priority > B->priority) {
			A->r = merge(A->r, B);
			return A->update();
		} else {
			B->l = merge(A, B->l);
			return B->update();
		}
	}
	template <typename... Ns>
	static node *merge(node *l, Ns... ns) {
		return merge(l, merge(ns...));
	}
};
