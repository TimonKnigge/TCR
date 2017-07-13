#include "../header.h"
#include "sequence.cpp"

struct EulerTourTree {
	vector<seq<int> *> seqs;
	// Create a new vertex.
	int add_vertex() {
		int id = (int)seqs.size() / 2;
		seq<int> *l = new seq<int>(2 * id), *r = new seq<int>(2 * id + 1);
		merge(l, r), seqs.push_back(l), seqs.push_back(r);
		return id;
	}
<<<<<<< HEAD
	// Find root of the subtree containg this vertex.
	int root(int u) { 
		seq<int> *s = seqs[2*u]->root();
		while (s->l != nullptr) s = s->l;
		return s->l->val / 2;
	}
=======
	// Find root of the subtree containing this vertex.
	int root(int u) { return seqs[2 * u]->root()->val / 2; }
>>>>>>> 97ee6c9350c05638fd02040b68428a1eeceea6fa
	// Cut from parent (if exists).
	void cut(int u) {
		seq<int> *uroot = seqs[2 * u]->root();
		int l = seqs[2 * u]->index(), r = seqs[2 * u + 1]->index();
		seq<int> *i1, *i2, *i3;
		tie(i2, i3) = split(uroot, r + 1);
		tie(i1, i2) = split(i2, l);
		merge(i1, i3);
	}
	// Whether u is an ancestor of v.
	bool ancestor(int u, int v) {
		if(root(u) != root(v)) return false;
		int lu = seqs[2 * u]->index(), ru = seqs[2 * u + 1]->index();
		int lv = seqs[2 * v]->index(), rv = seqs[2 * v + 1]->index();
		return lu <= lv && rv <= ru;
	}
	// Make v the parent of u. Assumes u has no parent!
	void attach(int u, int v) {
		seq<int> *vroot = seqs[2 * v]->root(), *i1, *i2;
		int end = seqs[2 * v + 1]->index();
		tie(i1, i2) = split(vroot, end);
		merge(i1, merge(seqs[2 * u]->root(), i2));
	}
	int size(int u) { return (seqs[2 * u]->root()->size + 1) / 2; }
};
