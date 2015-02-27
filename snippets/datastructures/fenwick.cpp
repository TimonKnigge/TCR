template <class T>
class FenwickTree {
private:
    vector<T> tree;
    int n;
public:
    FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
    T query(int l, int r) { return query(r) - query(l - 1); }
    T query(int r) {
        T s = 0;
        for(; r > 0; r -= (r & (-r))) s += tree[r];
        return s;
    }
    void update(int i, T v) {
        for(; i <= n; i += (i & (-i))) tree[i] += v;
    }
}; 