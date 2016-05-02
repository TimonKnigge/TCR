#include "../header.h"
struct Node {
	ll val, mx;
	int size, priority;
	bool rev = false;
	Node *l = NULL, *r = NULL;
	Node(ll _val) : val(_val), mx(_val), size(1) { priority = rand(); }
};
int size(Node *p) { return p == NULL ? 0 : p->size; }
ll getmax(Node *p) { return p == NULL ? -LLINF : p->mx; }
void update(Node *p) {
	if (p == NULL) return;
	p->size = 1 + size(p->l) + size(p->r);
	p->mx = max(p->val, max(getmax(p->l), getmax(p->r)));
}
void propagate(Node *p) {
	if (p == NULL || !p->rev) return;
	swap(p->l, p->r);
	if (p->l != NULL) p->l->rev ^= true;
	if (p->r != NULL) p->r->rev ^= true;
	p->rev = false;
}
void merge(Node *&t, Node *l, Node *r) {
	propagate(l); propagate(r);
	if (l == NULL)      { t = r; }
	else if (r == NULL) { t = l; }
	else if (l->priority > r->priority) {
		merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	update(t);
}
void split(Node *t, Node *&l, Node *&r, int at) {
	propagate(t);
	if (t == NULL) { l = r = NULL; return; }
	int id = size(t->l) + 1;
	if (id > at) { split(t->l, l, t->l, at); r = t; }
	else { split(t->r, t->r, r, at - id); l = t; }
	update(t);
}
void insert(Node *&t, ll val, int pos) {
	propagate(t);
	Node *n = new Node(val), *l, *r;
	split(t, l, r, pos);
	merge(t, l, n);
	merge(t, t, r);
}
void erase(Node *&t, int pos, bool del = true) {
	propagate(t);
	Node *L, *rm;
	split(t, t, L, pos);
	split(L, rm, L, 1);
	merge(t, t, L);
	if (del && rm != NULL) delete rm;
}
void reverse(Node *t, int l, int r) {
	propagate(t);
	Node *L, *R;
	split(t, t, L, l);
	split(L, L, R, r - l + 1);
	if (L != NULL) L->rev = true;
	merge(t, t, L);
	merge(t, t, R);
}
ll at(Node *t, int pos) {
	propagate(t);
	int id = size(t->l);
	if (pos == id) return t->val;
	else if (ps > id) return at(t->r, pos - id - 1);
	else return at(t->l, pos);
}
ll range_maximum(Node *t, int l, int r) {
	propagate(t);
	Node *L, *R;
	split(t, t, L, l);
	split(L, L, R, r - l + 1);
	ll ret = getmax(L);
	merge(t, t, L);
	merge(t, t, R);
	return ret;
}
void cleanup(Node *p) {
	if (p == NULL) return;
	cleanup(p->l); cleanup(p->r);
	delete p;
}
