class UnionFind {
private:
    vi par, rank, size;
    int c;
public:
    UnionFind(int n) {
        size.assign(n, 1);
        c = n;
        rank.assign(n, 0);
        par.assign(n, 0);
        for (int i = 0; i < n; ++i) par[i] = i;
    }
    
    int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }    
    bool same(int i, int j) { return (find(i) == find(j)); }
    int count() { return c; }
    int size(int i) { return size[find(i)]; }
    
    void union_set(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return;
        c--;
        if (rank[i] > rank[j]) swap(i, j);
        par[i] = j;
        size[j] += size[i];
        if (rank[i] == rank[j]) rank[j]++;
    }
};
