#include "../header.h"
struct Node {
	ll val;
	int size, priority;
	Node *l, *r;
	Node(ll _v) : val(_v), size(1) { priority = rand(); }
};

int size(Node *p) { return p == NULL ? 0 : p->size; }
void update(Node *p) {
	if (p == NULL) return;
	p->size = 1 + size(p->l) + size(p->r);
}
void merge(Node *&t, Node *l, Node *r) {
	if (l == NULL)      { t = r; }
	else if (r == NULL) { t = l; }
	else if (l->priority > r->priority) {
		merge(l->r, l->r, r); t = l;
	} else {
		merge(r->l, l, r->l); t = r;
	} update(t);
}
void split(Node *t, Node *&l, Node *&r, ll val) {
	if (t == NULL) { l = r = NULL; return; }
	if (t->val >= val) { // val goes with the right set
		split(t->l, l, t->l, val); r = t;
	} else {
		split(t->r, t->r, r, val); l = t;
	} update(t);
}
bool insert(Node *&t, ll val) {
	// returns false if the element already existed
	Node *n = new Node(val), *l, *r;
	split(t, l, t, val);
	split(t, t, r, val + 1);
	bool empty = (t == NULL);
	merge(t, l, n);
	merge(t, t, r);
	return empty;
}
void erase(Node *&t, ll val, bool del = true) {
	// returns false if the element did not exist
	Node *l, *rm;
	split(t, l, t, val);
	split(t, rm, t, val + 1);
	bool exists = (t != NULL);
	merge(t, l, t);
	if (del && rm != NULL) delete rm;
	return exists;
}
void cleanup(Node *p) {
	if (p == NULL) return;
	cleanup(p->l); cleanup(p->r);
	delete p;
}
