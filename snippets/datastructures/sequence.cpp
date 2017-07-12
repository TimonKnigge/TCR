#include "../header.h"
template <class T>
struct seq {
	T val; int size, priority;
	seq<T> *l = nullptr, *r = nullptr, *p = nullptr;
	seq(T _v) : val(_v), size(1) { priority = rand(); }

	seq<T> *update() {
		size = 1;
		if (l != nullptr) { l->p = this; size += l->size; }
		if (r != nullptr) { r->p = this; size += r->size; }
		return this;
	}
	// Find the root representing this sequence.
	seq<T> *root() {
		seq<T> *c = this;
		while (c->p != nullptr) c = c->p;
		return c;
	}
	int index() {
		int ind = (this->l != nullptr ? this->l->size : 0);
		seq<T> *c = this;
		while (c->p != nullptr) {
			if (c->p->l != c)
				ind += 1+(c->p->l != nullptr ? c->p->l->size : 0);
			c = c->p;
		}
		return ind;
	}
};

// Note: Assumes both nodes are the roots of their sequences.
template <class T>
seq<T> *merge(seq<T> *A, seq<T> *B) {
	if (A == nullptr) return B;
	if (B == nullptr) return A;
	if (A->priority > B->priority) {
		A->r = merge(A->r, B);
		return A->update();
	} else {
		B->l = merge(A, B->l);
		return B->update();
	}
}

// Split into [0, index) and [index, ..)
template<class T>
std::pair<seq<T>*, seq<T>*> split(seq<T> *A, int index) {
	if (A == nullptr) return {nullptr, nullptr};
	A->p = nullptr;
	int lsize = (A->l != nullptr ? A->l->size : 0);
	if (index <= lsize) {
		auto pr = split(A->l, index);
		A->l = pr.second;
		return {pr.first, A->update()};
	} else {
		auto pr = split(A->r, index - (1 + lsize));
		A->r = pr.first;
		return {A->update(), pr.second};
	}
}
