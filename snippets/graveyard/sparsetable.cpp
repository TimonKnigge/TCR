#include "../header.h"
using T = double; using vt = vector<T>; using vvt = vector<vt>;
struct SparseTable{
	vvt d;
	SparseTable(vt &a) : d(vvt{a}) {
		int N = a.size();
		for(auto s = 1; 2*s <= N; s *= 2){
			d.push_back(vt(N - 2*s + 1));
			auto &n = d.back(); auto &l = d[d.size()-2];
			for(int i = 0; i + 2*s<=N; ++i) n[i] = min(l[i], l[i+s]);
		}
	}
	int rmq(int l, int r){ // 0 <= l <= r < a.size()
		int p = 8*sizeof(int) - 1 - __builtin_clz(r+1-l);
		return min(d[p][l], d[p][r+1-(1<<p)]);
	}
};
