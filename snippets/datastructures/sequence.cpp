#include "../header.h"
template <class T>
struct seq {
	T val; int size_, priority;
	seq<T> *l = nullptr, *r = nullptr, *p = nullptr;
	seq(T _v) : val(_v), size_(1) { priority = rand(); }

	static int size(seq<T> *c) { return c == nullptr ? 0 : c->size_; }
	seq<T> *update() {
		size_ = 1;
		if(l != nullptr) l->p = this, size_ += l->size_;
		if(r != nullptr) r->p = this, size_ += r->size_;
		return this;
	}
	int index() {
		int ind = size(this->l);
		seq<T> *c = this;
		while(c->p != nullptr) {
			if(c->p->l != c) ind += 1 + size(c->p->l);
			c = c->p;
		}
		return ind;
	}
	seq<T> *root() { return this->p == nullptr ? this : p->root(); }
	seq<T> *min() { return this->l == nullptr ? this : l->min(); }
	seq<T> *max() { return this->r == nullptr ? this : r->max(); }
	seq<T> *next() { return this->r == nullptr ? this->p : this->r->min(); }
	seq<T> *prev() { return this->l == nullptr ? this->p : this->l->max(); }
};

// Note: Assumes both nodes are the roots of their sequences.
template <class T>
seq<T> *merge(seq<T> *A, seq<T> *B) {
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
template <class T, typename... Seqs>
seq<T> *merge(seq<T> *l, Seqs... seqs) {
	return merge(l, merge(seqs...));
}

// Split into [0, index) and [index, ..)
template <class T>
pair<seq<T> *, seq<T> *> split(seq<T> *A, int index) {
	if(A == nullptr) return {nullptr, nullptr};
	A->p = nullptr;
	if(index <= seq<T>::size(A->l)) {
		auto pr = split(A->l, index);
		A->l = pr.second;
		return {pr.first, A->update()};
	} else {
		auto pr = split(A->r, index - (1 + seq<T>::size(A->l)));
		A->r = pr.first;
		return {A->update(), pr.second};
	}
}

// TODO: a dedicated function not using index would be faster
// return [0, x), [x, ..)
template <class T>
pair<seq<T> *, seq<T> *> split(seq<T> *root, seq<T> *x) {
	return split(root, x->index());
}
