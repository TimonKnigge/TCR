#include "../header.h"
#include "sequence.cpp"
template <class T, void M(const T *, T *, const T *) = T::merge>
struct EulerTourForest {
	struct edge {
		T val;
		int u, v;
		static void merge(const edge *l, edge *m, const edge *r) {
			M(l ? &l->val : nullptr, m->val, r ? &r->val : nullptr);
		}
	};
	using node = seq<edge>;
	using ptr = std::unique_ptr<node>;
	struct edge_handler : array<ptr, 2> {
		edge_handler(edge_handler &&e) : array<ptr, 2>{move(e)} {
			for(auto &p : e) p.reset();
		}
		edge_handler(ptr &&l, ptr &&r) : array<ptr, 2>{{move(l), move(r)}} {}
	};
	vector<node> nodes; // one node for each vertex
	EulerTourForest(int n = 0) {
		nodes.reserve(n);
		while(n--) add_vertex();
	}
	int add_vertex() {
		int v = nodes.size();
		nodes.emplace_back(edge{v, v});
		return v;
	}
	int root(int v) { return nodes[v].root()->max()->val.u; }
	node *reroot(node *x) {
		if(x == nullptr) return x;
		auto lr = split(x);
		return merge(lr.second, lr.first);
	}
	void reroot(int v) { reroot(&nodes[v]); }
	void cut(edge_handler &&e) {
		if(e[0]->index() > e[1]->index()) swap(e[0], e[1]);
		auto x = split(e[0].get()).first;       // xeyez -> (x,eyez)
		auto ey_ez = split(e[1].get());         // eyez  -> (ey,ez)
		split(ey_ez.first, 1).second;           // ey    -> (e,y)
		auto z = split(ey_ez.second, 1).second; // ez    -> (e,z)
		merge(x, z); // the edge_handler will be destructed at the end.
	}
	edge_handler link(int u, int v) {
		auto x = reroot(&nodes[u]), y = &nodes[v];
		auto a_vb = split(y); // or v->index()+1
		edge_handler e{ptr{new node{{v, u}}}, ptr{new node{{u, v}}}};
		::merge(a_vb.first, e[0].get(), x, e[1].get(), a_vb.second);
		return e;
	}
	int size(int u) { return (nodes[u].root()->size_ + 2) / 3; }
	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
};
