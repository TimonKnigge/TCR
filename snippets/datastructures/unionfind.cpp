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
        if ((i = find_set(i)) == (j = find_set(j))) return;
        setCount--;
        if (rank[i] > rank[j]) {
            parent[j] = i;
            setSize[i] += setSize[j];
        } else {
            parent[i] = j;
            setSize[i] += setSize[i];
            if (rank[i] == rank[j]) rank[j]++;
        }
    }
};