#include "../header.h"
#define MAX_N 1000

vvi children;

int L[2*MAX_N], E[2*MAX_N], H[MAX_N], idx;

void dfs(int cur, int depth) {
	H[cur] = idx;
	E[idx] = cur;
	L[idx++] = depth;
	for(auto &child : children[cur]){
		dfs(child, depth+1);
		E[idx] = cur; // backtrack to current node
		L[idx++] = depth;
	}
}

void buildRMQ() {
	idx = 0;
	fill_n(H, MAX_N, -1);
	dfs(0, 0); // we assume that the root is at index 0
}
