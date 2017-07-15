#include "../header.h"
#include "./splay_tree.cpp"

struct link_cut_forest {
	struct node : splay_tree_node<node *> {
		using splay_tree_node::splay_tree_node;
		void access(node *v = nullptr) {
			this->splay();
			if(this->r) {
				this->r->val = this;
				if(v) {
					this->r->p = nullptr;
					this->r = v;
					v->val = nullptr;
				} else
					this->unright();
			}
			if(this->val) this->val->access(this);
		}
		node *lc_root() {
			access();
			return up(this->min()->splay());
		}
		static node *up(splay_tree_node *s) { return static_cast<node *>(s); }
	};
	vector<node> nodes;
	link_cut_forest(int n = 0) : nodes(n) {}
	int add_vertex() {
		nodes.emplace_back(nullptr);
		return nodes.size() - 1;
	}

	// cut this loose of the tree; returns the other component
	node *cut() {
		access();
		node *l = up(this->l);
		this->unleft();
		return l;
	}

	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
	void link(node *x, node *y) {
		x->access();
		y->access();
		x->left(y);
	}
	void link(int u, int v) { link(&nodes[u], &nodes[y]) }
};

// todo: use the internal splay tree pointer for path parent
// http://codeforces.com/contest/117/submission/860934
// http://www.spoj.com/problems/DYNALCA/

int main() {
	link_cut_tree t;
	t.add_vertex();
}
