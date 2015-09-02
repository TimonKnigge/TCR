#include "../header.h"
#include "../graphs/tarjan.cpp"
struct TwoSAT {
	int n;
	vvi imp; // implication graph
	Tarjan tj;

	TwoSAT(int _n) : n(_n), imp(2 * _n, vi()), tj(imp) { }

	// Only copy the needed functions:
	void add_implies(int c1, bool v1, int c2, bool v2) {
		int u = 2 * c1 + (v1 ? 1 : 0),
			v = 2 * c2 + (v2 ? 1 : 0);
		imp[u].push_back(v);		//  u =>  v
		imp[v^1].push_back(u^1);	// -v => -u
	}
	void add_equivalence(int c1, bool v1, int c2, bool v2) {
		add_implies(c1, v1, c2, v2);
		add_implies(c2, v2, c1, v1);
	}
	void add_or(int c1, bool v1, int c2, bool v2) {
		add_implies(c1, !v1, c2, v2);
	}
	void add_and(int c1, bool v1, int c2, bool v2) {
		add_true(c1, v1); add_true(c2, v2);
	}
	void add_xor(int c1, bool v1, int c2, bool v2) {
		add_or(c1, v1, c2, v2);
		add_or(c1, !v1, c2, !v2);
	}
	void add_true(int c1, bool v1) {
		add_implies(c1, !v1, c1, v1);
	}

	// on true: a contains an assignment.
	// on false: no assignment exists.
	bool solve(vb &a) {
		vi com;
		tj.find_sccs(com);
		for (int i = 0; i < n; ++i)
			if (com[2 * i] == com[2 * i + 1])
				return false;

		vvi bycom(com.size());
		for (int i = 0; i < 2 * n; ++i)
			bycom[com[i]].push_back(i);

		a.assign(n, false);
		vb vis(n, false);
		for(auto &&component : bycom){
			for (int u : component) {
				if (vis[u / 2]) continue;
				vis[u / 2] = true;
				a[u / 2] = (u % 2 == 1);
			}
		}
		return true;
	}
};

