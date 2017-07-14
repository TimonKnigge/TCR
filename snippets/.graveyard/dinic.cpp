#include "../header.h"
#include "flownetwork.cpp"
#define MAXV 5000
ll FlowNetwork::dinic_augment(int s, int t, int* d, ll cap) {
	if (s == t) return cap;
	ll f = 0, df = 0;
	for (int i = h[s]; i != -1; i = e[i].nxt) {
		if (e[i].cap > e[i].flo && d[s] + 1 == d[e[i].v]) {
			f += (df = dinic_augment(e[i].v, t, d, min(cap, e[i].cap - e[i].flo)));
			e[i].flo += df;
			e[i ^ 1].flo -= df;
			if((cap -= df) == 0) break;
		}	}
	return f;
}

ll FlowNetwork::dinic(int s, int t) {
	int q[MAXV], d[MAXV]; ll f = 0;
	while (true) {
		memset(d, -1, n * sizeof(int));
		int l = 0, r = 0, u = -1, i;
		d[q[r++] = s] = 0;
		while (l != r && u != t)
			for (u = q[l++], i = h[u]; i != -1; i = e[i].nxt)
				if (e[i].cap > e[i].flo && d[e[i].v] == -1)
					d[q[r++] = e[i].v] = d[u] + 1;
		if (d[t] == -1) break;
		f += dinic_augment(s, t, d, LLINF);
	}
	return f;
}
