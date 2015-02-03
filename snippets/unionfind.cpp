vii pset;
int psets;

class UnionFind {
private:
    vi parent, rank, setSize;
    int setCount;
public:
    UnionFind(int N) {
        setSize.assign(N, 1);
        setCount = N;
        rank.assign(N, 0);
        parent.assign(N, 0);
        
        for (int i = 0; i < N; ++i) parent[i] = i;
    }
    
    int find_set(int i) {
        return (parent[i] == i) ? i : (parent[i] = find_set(parent[i]));
    }
    
    bool are_same_set(int i, int j) {
        return (find_set(i) == find_set(j));
    }
    
    void union_set(int i, int j) {
        if (are_same_set(i, j)) return;
        setCount--;
        int pi = find_set(i), pj = find_set(j);
        if (rank[pi] > rank[pj]) {
            parent[pj] = pi;
            setSize[pi] += setSize[pj];
        } else {
            parent[pi] = pj;
            setSize[pj] += setSize[pi];
            if (rank[pi] == rank[pj])) rank[pj]++;
        }
    }
}