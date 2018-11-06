#include "../header.h"
void fsc(vi &a, bool inverse = false) {
	for (int s = 1, k = (int)a.size(); s < k; s <<= 1)
		for (int i = 0; i < k; ++i)
			if (!(i&s))
				a[i|s] += a[i] * (!inverse ? 1 : -1);
}
