#include "../header.h"
#include "../utils/hash.cpp"
#include "./euler-tour-tree-edges.cpp"

struct dynamic_graph_connectivity {
	struct node_data {
		int cur, sum; // number of incident edges on current level
		int size;     // size of subtree
		node_data() : cur(0), sum(0), size(1) {}
		static void merge(const node_data *l, node_data *m,
		                  const node_data *r) {
			m->sum = m->cur, m->size = 1;
			if(l) m->sum += l->sum, m->size += l->size;
			if(r) m->sum += r->sum, m->size += r->size;
		}
	};
	using etf = euler_tour_forest<node_data>;
	struct edge_data {
		int level;
		array<list<int>::iterator, 2> list_pos;
		vector<etf::edge_handler> tree_nodes; // pointers to tree edges
	};

	// The forest for each level
	vector<etf> F;
	// The adjacency lists for each level
	vector<vector<list<int>>> adj;
	// Edge data: which level and where in the adjacency lists
	unordered_map<pair<int, int>, edge_data> edges;

	dynamic_graph_connectivity(int n) {
		int lgn = 0;
		for(int _n = n; _n > 0; _n /= 2, ++lgn)
			;
		F.assign(lgn, etf(n));
		adj.resize(lgn);
		for(auto &x : adj) x.resize(n);
	}

	bool connected(int u, int v) { return F[0].connected(u, v); }

	void update_edge_counter(int l, int u, int v, int delta) {
		F[l].nodes[u].val.val.cur += delta;
		F[l].update(u);
		F[l].nodes[v].val.val.cur += delta;
		F[l].update(v);
	}

	void push_level(int l, int u, int v) { // push {u,v} from level l to l+1
		assert(u < v);
		// B: update edge info
		auto it = edges.find({u, v});
		auto &edge_info = it->second;
		assert(l == edge_info.level);
		++edge_info.level;

		// A: move to adjacency list at next level
		//    the edge_info.list_pos iterators remain valid because of
		//    splicing
		adj[l + 1][u].splice(adj[l + 1][u].end(), adj[l][u],
		                     edge_info.list_pos[0]);
		adj[l + 1][v].splice(adj[l + 1][v].end(), adj[l][v],
		                     edge_info.list_pos[1]);

		// C: add uv to the next level tree if not yet connected
		if(!F[l + 1].connected(u, v)) {
			// add edge to tree and store it's handlers pointers
			auto eh = F[l + 1].link(u, v);
			edge_info.tree_nodes.emplace_back(move(eh));
		}

		// D: update incidence count
		update_edge_counter(l, u, v, -1);
		update_edge_counter(l + 1, u, v, 1);
	};

	void link(int u, int v) {
		if(u > v) swap(u, v);
		int level = 0;
		// A: adjacency list for level
		adj[level][u].push_back(v);
		auto i0 = --adj[level][u].end();
		adj[level][v].push_back(u);
		auto i1 = --adj[level][v].end();

		// B: edge data
		auto &edge_info =
		    edges.emplace(pair<int, int>{u, v}, edge_data{0, {{i0, i1}}, {}})
		        .first->second;

		// C: part of tree
		if(!F[level].connected(u, v)) {
			// add edge to tree and store it's handlers pointers
			auto eh = F[level].link(u, v);
			edge_info.tree_nodes.emplace_back(move(eh));
		}

		// D: increase incidence count
		update_edge_counter(0, u, v, 1);
	}
	void cut(int u, int v) {
		if(u > v) swap(u, v);
		// 1: Remove the current edge

		// get the edge info
		auto it = edges.find({u, v});
		auto &edge_info = it->second;
		int level = edge_info.level;

		// ~D: decrease incidence count
		update_edge_counter(level, u, v, -1);

		// ~C: remove from level trees if needed
		bool intree = !edge_info.tree_nodes.empty();
		if(intree) {
			for(int l = level; l >= 0; --l)
				F[l].cut(move(edge_info.tree_nodes[l]));
			edge_info.tree_nodes.clear();
		}

		// ~A: remove from adjacency list for level (depends on B)
		adj[level][u].erase(edge_info.list_pos[0]);
		adj[level][v].erase(edge_info.list_pos[1]);

		// ~B: remove from edges
		edges.erase(it);

		if(!intree) return;

		// remove from level adjacency list
		// remove from trees

		// 2: Find a replacement edge. Start the search at level,
		// continue with lower levels until level 0 has been reached
		for(int l = level; l >= 0; --l) {
			// a) we sort u and v such that the component size of v is
			// smaller
			if(F[l].nodes[u].root()->val.val.size <
			   F[l].nodes[v].root()->val.val.size)
				swap(u, v);

			// b) we can afford to push all edges in T_v to the next level
			//    (but no need to this this; just shows that (c) is allowed)

			// c) iterate over level i edges incident to T_v at x.
			//  - if y in T_u: add xy to F_0 .. F_level and stop
			//  - otherwise level the level of the edge

			// dfs T_v while skipping subtrees with node_data::sum == 0
			stack<etf::node *> s;
			auto v_root = F[l].nodes[v].root();
			auto u_root = F[l].nodes[u].root();
			s.push(v_root);

			while(!s.empty()) {
				auto cur = s.top();
				s.pop();

				// nothing to see here
				if(cur->val.val.sum == 0) continue;

				// succes! Start processing edges incident to this vertex
				if(cur->val.val.cur > 0) {
					assert(cur->val.u == cur->val.v);
					// x is the current vertex in T_v
					int x = cur->val.u;
					// loop over edges on level incident to x
					assert(cur->val.val.cur == int(adj[l][x].size()));
					// it is incremented within the loop, because we might
					// remove edges from the list
					for(auto it = adj[l][x].begin(); it != adj[l][x].end();) {
						int y = *it;
						auto y_root = F[l].nodes[y].root();
						// y in T_u?
						if(y_root == u_root) {
							// success: add (x,y) to F_l ... F_0
							for(int i = l; i >= 0; --i) {
								auto eh = F[i].link(x, y);
								auto &edge_info =
								    edges.find({min(x, y), max(x, y)})
								        ->second;
								edge_info.tree_nodes.emplace_back(move(eh));
							}
							return;
						} else {
							// failure: push (x,y) to level l+1
							it = next(it);
							push_level(l, min(x, y), max(x, y));
						}
					}
				}
				// go on with children
				if(cur->l && cur->l->val.val.sum > 0) s.push(cur->l);
				if(cur->r && cur->r->val.val.sum > 0) s.push(cur->r);
			}
		}
	}
};
