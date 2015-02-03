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
    
    int findSet(int i) {
        return (parent[i] == i) ? i : (parent[i] = findSet(parent[i]));
    }
    
    bool areSameSet(int i, int j) {
        return (findSet(i) == findSet(j));
    }
    
    void unionSet(int i, int j) {
        if (areSameSet(i, j)) return;
        setCount--;
        int pi = findSet(i), pj = findSet(j);
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