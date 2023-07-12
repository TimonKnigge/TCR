#include "../header.h"
struct UnionFind {
	std::vector<int> par, rank, size;
	int c;
	UnionFind(int n) : par(n), rank(n, 0), size(n, 1), c(n) {
		for(int i = 0; i < n; ++i) par[i] = i;
	}
	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }
	int merge(int i, int j) {
		if((i = find(i)) == (j = find(j))) return -1;
		--c;
		if(rank[i] > rank[j]) swap(i, j);
		par[i] = j;
		size[j] += size[i];
		if(rank[i] == rank[j]) rank[j]++;
		return j;
	}
};
