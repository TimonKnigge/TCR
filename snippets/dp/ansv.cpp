#include "header.h"
void all_nearest_smaller_values(vi &a, vi &b) {
	b.assign(a.size(), -1);
	for (int i = 1; i < b.size(); ++i) {
		b[i] = i - 1;
		while (b[i] >= 0 && a[i] < a[b[i]])
			b[i] = b[b[i]];
	}
}

