#include "header.h"
class UnionFind {                  
	private:
		vi p, r, s; // parent, rank, set size (may be omitted)
		int numSets;// number of sets
	public:
		UnionFind(int N) {
			s.assign(N, 1); numSets = N; r.assign(N, 0);
			p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
		int find(int i) { return (p[i] == i) ? i : (p[i] = find(p[i])); }
		bool same(int i, int j) { return find(i) == find(j); }
		void merge(int i, int j) { 
			if (!same(i, j)) {
				numSets--; 
				int x = find(i), y = find(j);
				if (r[x] > r[y]) swap(x,y); 
				p[x] = y; s[y] += s[x];
				if (r[x] == r[y]) r[y]++; 
			}
		}
		int components() { return numSets; }
		int size(int i) { return s[find(i)]; }
};
