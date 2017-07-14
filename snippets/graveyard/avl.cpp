#include "../header.h"
template <class T>
struct AVL_Tree {
	struct AVL_Node {
		T val;
		AVL_Node *p, *l, *r;
		int size, height;
		AVL_Node(T &_val, AVL_Node *_p = NULL)
		 : val(_val), p(_p), l(NULL), r(NULL), size(1), height(0) { }
	};
	AVL_Node *root;
	AVL_Tree() : root(NULL) { }

	// Querying
	AVL_Node *find(T &key) { // O(lg n)
		AVL_Node *c = root;
		while (c != NULL && c->val != key) {
			if (c->val < key) c = c->r;
			else c = c->l;
		}
		return c;
	}
	// maximum and predecessor can be written in a similar manner
	AVL_Node *minimum(AVL_Node *n) { // O(lg n)
		if (n != NULL) while (n->l != NULL) n = n->l; return n;
	}
	AVL_Node *minimum() { return minimum(root); } // O(lg n)
	AVL_Node *successor(AVL_Node *n) { // O(lg n)
		if (n->r != NULL) return minimum(n->r);
		AVL_Node *p = n->p;
		while (p != NULL && n == p->r) { n = p; p = n->p; }
		return p;
	}

	// Modification
	AVL_Node *insert(T &nval) { // O(lg n)
		AVL_Node *p = NULL, *c = root;
		while (c != NULL) {
			p = c;
			c = (c->val < nval ? c->r : c->l);
		}
		AVL_Node *r = new AVL_Node(nval, p);
		(p == NULL ? root : (
			nval < p->val ? p->l : p->r)) = r;
		_fixup(r);
		return r;
	}
	void remove(AVL_Node *n, bool del = true) { // O(lg n)
		if (n == NULL) return;
		if (n->l != NULL && n->r != NULL) {
			AVL_Node *y = successor(n), *z = y->par;
			if (z != n) {
				_transplant(y, y->r);
				y->r = n->r;
				y->r->p = y;
			}
			_transplant(n, y);
			y->l = n->l;
			y->l->p = y;
			_fixup(z->r == NULL ? z : z->r);
			if (del) delete n;
			return;
		} else if (n->l != NULL) {
			_pchild(n) = n->l;
			n->l->p = n->p;
		} else if (n->r != NULL) {
			_pchild(n) = n->r;
			n->r->p = n->p;
		} else _pchild(n) = NULL;
		_fixup(n->p);
		if (del) delete n;
	}
	void cleanup() { _cleanup(root); }

	// Helpers
	void _transplant(AVL_Node *u, AVL_Node *v) {
		_pchild(u) = v;
		if (v != NULL) v->p = u->p;
	}
	AVL_Node *&_pchild(AVL_Node *n) {
		return (n == NULL ? root : (n->p == NULL ? root :
			(n->p->l == n ? n->p->l : n->p->r)));
	}
	void _augmentation(AVL_Node *n) {
		if (n == NULL) return;
		n->height = 1 + max(_get_height(n->l), _get_height(n->r));
		n->size = 1 + _get_size(n->l) + _get_size(n->r);
	}
	int _get_height(AVL_Node *n) { return (n == NULL ? 0 : n->height); }
	int _get_size(AVL_Node *n) { return (n == NULL ? 0 : n->size); }
	bool _balanced(AVL_Node *n) {
		return (abs(_get_height(n->l) - _get_height(n->r)) <= 1);
	}
	bool _leans_left(AVL_Node *n) {
		return _get_height(n->l) > _get_height(n->r);
	}
	bool _leans_right(AVL_Node *n) {
		return _get_height(n->r) > _get_height(n->l);
	}
#define ROTATE(L, R) \
	AVL_Node *o = n->R; \
	n->R = o->L; \
	if (o->L != NULL) o->L->p = n; \
	o->p = n->p; \
	_pchild(n) = o; \
	o->L = n; \
	n->p = o; \
	_augmentation(n); \
	_augmentation(o);
	void _left_rotate(AVL_Node *n) { ROTATE(l, r); }
	void _right_rotate(AVL_Node *n) { ROTATE(r, l); }
	void _fixup(AVL_Node *n) {
		while (n != NULL) {
			_augmentation(n);
			if (!_balanced(n)) {
				if (_leans_left(n)&&_leans_right(n->l)) _left_rotate(n->l);
				else if (_leans_right(n) && _leans_left(n->r))
					_right_rotate(n->r);
				if (_leans_left(n)) _right_rotate(n);
				if (_leans_right(n)) _left_rotate(n);
			}
			n = n->p;
		}
	}
	void _cleanup(AVL_Node *n) {
		if (n->l != NULL) _cleanup(n->l);
		if (n->r != NULL) _cleanup(n->r);
	}
};
