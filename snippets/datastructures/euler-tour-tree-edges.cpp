#include "../header.h"
#include "./sequence.cpp"
#include "./splay_tree.cpp"
struct empty_t {};
// provides: add_vertex, link(int,int), cut(eh), connected(int,int), size(int)
template <class T = empty_t, void M(const T *, T *, const T *) = nullptr>
struct euler_tour_forest {
	struct edge {
		int u, v;
		T val;
		static void merge(const edge *l, edge *m, const edge *r) {
			M(l ? &l->val : nullptr, m->val, r ? &r->val : nullptr);
		}
	};
	// using node = seq<edge>;
	using node = splay_tree_node<edge>;
	using ptr = std::unique_ptr<node>;
	struct edge_handler : array<ptr, 2> {
		edge_handler(edge_handler &&e) : array<ptr, 2>{move(e)} {
			for(auto &p : e) p.reset();
		}
		edge_handler(ptr &&l, ptr &&r) : array<ptr, 2>{{move(l), move(r)}} {}
	};
	vector<node> nodes; // one node for each vertex
	euler_tour_forest(int n = 0) {
		nodes.reserve(n);
		while(n--) add_vertex();
	}
	int add_vertex() {
		int v = nodes.size();
		nodes.emplace_back(edge{v, v});
		return v;
	}
	node *reroot(node *x) {
		if(x == nullptr) return x;
		typename node::node_pr lr;
		lr = x->split();
		return node::merge(lr.second, lr.first);
	}
	void cut(edge_handler &&e) {
		auto x_eyez = e[0]->split();                  // or xey|ez
		auto yez = x_eyez.second->splitleft().second; // or z
		if(e[1]->root() == yez)
			node::merge(x_eyez.first,
			            e[1]->split().second->splitleft().second);
		else
			node::merge(e[1]->splitleft().first->split().first, yez);
	}
	edge_handler link(int u, int v) {
		auto x = reroot(&nodes[u]), y = &nodes[v];
		auto a_vb = y->split();
		edge_handler e{ptr{new node{{v, u}}}, ptr{new node{{u, v}}}};
		node::merge(a_vb.first, e[0].get(), x, e[1].get(), a_vb.second);
		return e;
	}
	int size(int u) { return (nodes[u].root()->size_ + 2) / 3; }
	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
};
