#include "../header.h"
struct Node {
	ll v;
	int sz, pr;
	Node *l = nullptr, *r = nullptr;
	Node(ll val) : v(val), sz(1) { pr = rand(); }
};
int size(Node *p) { return p ? p->sz : 0; }
void update(Node* p) {
	if (!p) return;
	p->sz = 1 + size(p->l) + size(p->r);
	// Pull data from children here
}
void propagate(Node *p) {
	if (!p) return;
	// Push data to children here
}
void merge(Node *&t, Node *l, Node *r) {
	propagate(l), propagate(r);
	if (!l)			t = r;
	else if (!r)	t = l;
	else if (l->pr > r->pr)
			merge(l->r, l->r, r), t = l;
	else	merge(r->l, l, r->l), t = r;
	update(t);
}
void spliti(Node *t, Node *&l, Node *&r, int index) {
	propagate(t);
	if (!t) { l = r = nullptr; return; }
	int id = size(t->l);
	if (index <= id) // id \in [index, \infty), so move it right
		spliti(t->l, l, t->l, index), r = t;
	else
		spliti(t->r, t->r, r, index - id), l = t;
	update(t);
}
void splitv(Node *t, Node *&l, Node *&r, ll val) {
	propagate(t);
	if (!t) { l = r = nullptr; return; }
	if (val <= t->v) // t->v \in [val, \infty), so move it right
		splitv(t->l, l, t->l, val), r = t;
	else
		splitv(t->r, t->r, r, val), l = t;
	update(t);
}
void clean(Node *p) {
	if (p) { cleanup(p->l), cleanup(p->r); delete p; }
}
