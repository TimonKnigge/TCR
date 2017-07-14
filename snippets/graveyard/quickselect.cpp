#include "../header.h"
template<class T>
T quickselect(vector<T> &v, int l, int r, int k) {
	int p = l + (rand() % (r - l));
	swap(v[l], v[p]);
	bool alt = false; p = l + 1;
	for (int j = l + 1; j < r; ++j) {
		if (alt = !alt) {
			   if (v[j] <  v[l]) swap(v[p++], v[j]);
		} else if (v[j] <= v[l]) swap(v[p++], v[j]);
	}
	swap(v[l], v[--p]);

	if (p == k) return v[k];
	if (p >  k) return quickselect(v, l, p, k);
	if (p <  k) return quickselect(v, p + 1, r, k);
}