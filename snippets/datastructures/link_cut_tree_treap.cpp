#include "../header.h"
#include "./sequence_link_cut_tree.cpp"
struct link_cut_forest_treap {
	struct node;
	struct T {
		size_t v;
		// int x = 0, sx = 0;	// for sum aggregate
		node *pp = nullptr;
		bool reverse = false;
		void toggle() { reverse = !reverse; }
	};
	// void update(int u, int count) { nodes[u].access()->val.x = count; }
	struct node : seq<node, T> {
		using seq::seq;
		node *access(bool lca = false) { // set for lca queries
			log_scope _("access", this, this->root());
			auto lr = this->split(false);
			node *root = lr.first;
			if(lr.second) {
				//_.print("P1", this, this->root(), lr.second);
				if(lr.second && lr.second->val.pp)
					swap(lr.first->val.pp, lr.second->val.pp);
				//_.print("P2", this, this->root(), lr.second);
				lr.second->val.pp = this;
			}
			//_.print("P3", this, this->root(), r);
			node *last = this;
			while(node *w = root->val.pp) {
				log_scope _("while", w, w->root(), this, this->root());
				last = w;
				root->val.pp = nullptr;
				auto lr = w->split(false);
				if(lr.second) {
					log_scope _("fix pps", lr.first, lr.second);
					if(lr.second && lr.second->val.pp)
						swap(lr.first->val.pp, lr.second->val.pp);
					lr.second->val.pp = w;
				}
				root = node::merge(lr.first, root->root());
				//_.leave("W,this", w, this);
				//_.leave("Roots", w->root(), this->root());
			}
			//_.leave(this, this->root());
			if(lca) return last;
			return this;
		}
		node *lc_root() { return access()->root()->min() /*->splay()*/; }
		node *parent() {
			node *previous = this->prev();
			if(previous) return previous;
			return this->root()->val.pp;
		}
		virtual node *u() {
			if(val.pp == nullptr) {
				if(l && l->val.pp) swap(val.pp, l->val.pp);
				if(r && r->val.pp) swap(val.pp, r->val.pp);
			}
			return this;
			/*
			val.sx = val.x;
			if(l) val.sx += l->val.sx;
			if(r) val.sx += r->val.sx;
			*/
		}
		virtual node *n() {
			if(this->val.reverse) {
				swap(this->l, this->r);
				if(this->l) this->l->val.toggle();
				if(this->r) this->r->val.toggle();
				this->val.reverse = false;
			}
			return this;
		}

		friend ostream &operator<<(ostream &o, const node &x) {
			o << '(';
			if(x.l)
				o << *x.l;
			else
				o << '-';
			o << x.val.v;
			// o<< (x.val.reverse ? 'R' : '.') << x.val.x << x.val.sx;
			if(x.r)
				o << *x.r;
			else
				o << '-';
			o << ")";
			if(x.isroot()) {
				o << " ->> ";
				if(x.val.pp)
					o << x.val.pp->val.v;
				else
					o << '-';
			} else {
				if(x.val.pp) o << '*';
			}
			return o;
		}
	};
	vector<node> nodes;
	link_cut_forest_treap(int n = 0) : nodes(n) {
		for(int i = 0; i < n; ++i) nodes[i].val.v = i;
	}
	int add_vertex() {
		nodes.push_back(T{nodes.size()});
		return nodes.size() - 1;
	}
	node *reroot(node *x) {
		x->access()->root()->val.toggle();
		return x;
	}
	void cut(node *x) { x->access()->split(); }
	void cut(int v) { cut(&nodes[v]); } // cut v from parent
	void cut(int u, int v) {
		if(&nodes[v] == nodes[u].parent())
			cut(&nodes[u]);
		else
			cut(&nodes[v]);
	}
	bool connected(int u, int v) {
		return nodes[u].lc_root() == nodes[v].lc_root();
	}
	void attach(int u, int v) { // u must be root; make child of v
		log_scope _("attach", nodes[u], nodes[v]);
		assert(nodes[u].l == nullptr);
		nodes[u].access()->left(nodes[v].access()->root());
		//_.leave(nodes[u], nodes[v], nodes[v].root());
	}
	void link(node *x, node *y) { // will reroot x
		reroot(x)->access()->left(y->access()->root());
	}
	void link(int u, int v) { link(&nodes[u], &nodes[v]); } // u child of v
	int lca(int u, int v) {
		nodes[u].access();
		return nodes[v].access(true) - &nodes[0];
	}
};
ostream &operator<<(ostream &o, const link_cut_forest_treap::node *x) {
	if(x) return o << *x;
	return o << '-';
}

// todo: use the internal splay tree pointer for path parent
// http://codeforces.com/contest/117/submission/860934
// http://www.spoj.com/problems/DYNACON1/
// http://www.spoj.com/problems/DYNACON2/
// http://www.spoj.com/problems/DYNALCA/
