#include "../header.h"
template <class T, void M(const T *, T *, const T *) = nullptr>
struct seq {
	T val;
	int size_, priority;
	seq<T, M> *l = nullptr, *r = nullptr, *p = nullptr;
	seq(T _v) : val(_v), size_(1) { priority = rand(); }
	static int size(seq<T, M> *c) { return c ? c->size_ : 0; }
	seq<T, M> *update() {
		size_ = 1;
		if (l) l->p = this, size_ += l->size_;
		if (r) r->p = this, size_ += r->size_;
		if (M) M(l ? &l->val : nullptr, &this->val, r ? &r->val : nullptr);
		return this;
	}
	int index() {
		int ind = size(this->l);
		seq<T, M> *c = this;
		while (c->p) {
			if (c->p->l != c) ind += 1 + size(c->p->l);
			c = c->p;
		}
		return ind;
	}
	seq<T, M> *root() { return this->p ? p->root() : this; }
	seq<T, M> *min() { return this->l ? l->min() : this; }
	seq<T, M> *max() { return this->r ? r->max() : this; }
	seq<T, M> *next() { return this->r ? this->r->min() : this->p; }
	seq<T, M> *prev() { return this->l ? this->l->max() : this->p; }
};
// Note: Assumes both nodes are the roots of their sequences.
template <class T, void M(const T *, T *, const T *)>
seq<T, M> *merge(seq<T, M> *A, seq<T, M> *B) {
	if (!A) return B;
	if (!B) return A;
	if (A->priority > B->priority) {
		A->r = merge(A->r, B);
		return A->update();
	} else {
		B->l = merge(A, B->l);
		return B->update();
	}
}
// Note: Assumes all nodes are the roots of their sequences.
template <class T, void M(const T *, T *, const T *), typename... Seqs>
seq<T, M> *merge(seq<T, M> *l, Seqs... seqs) {
	return merge(l, merge(seqs...));
}
// Split into [0, index) and [index, ..)
template <class T, void M(const T *, T *, const T *)>
pair<seq<T, M> *, seq<T, M> *> split(seq<T, M> *A, int index) {
	if (!A) return {nullptr, nullptr};
	A->p = nullptr;
	if (index <= seq<T, M>::size(A->l)) {
		auto pr = split(A->l, index);
		A->l = pr.second;
		return {pr.first, A->update()};
	} else {
		auto pr = split(A->r, index - (1 + seq<T, M>::size(A->l)));
		A->r = pr.first;
		return {A->update(), pr.second};
	}
}
// return [0, A), [A, ..)
template <class T, void M(const T *, T *, const T *)>
pair<seq<T, M> *, seq<T, M> *> split(seq<T, M> *A) {
	if (!A) return {nullptr, nullptr};
	seq<T, M> *B = A, *lr = A;
	A = A->l;
	if (!A) {
		while (lr->p && lr->p->l == B) lr = B = lr->p;
		if (lr->p)
			lr = A = lr->p, lr->r = B->p = nullptr;
	} else
		A->p = lr->l = nullptr;
	while (lr->update()->p) {
		if (lr->p->l == lr) {
			if (lr == A) swap(A->p, B->p), B->p->l = B;
			lr = B = B->p;
		} else {
			if (lr == B) swap(A->p, B->p), A->p->r = A;
			lr = A = A->p;
		}
	}
	return {A, B};
}
