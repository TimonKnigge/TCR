#include "../header.h"
#define MAX_N 15
ll d[MAX_N][MAX_N];

ll meet_in_the_middle(int n) {
	int half = (n - 2) / 2, otherhalf = n - 2 - half;
	vi leftroute(half, 0), rightroute(otherhalf, 0);
	ll shortest = LLINF;

	for (int m = 1; m < n; ++m) {
		int mask = (1 << half) - 1;
		while (!(mask & 1 << (n - 2))) {
			int l = 0, r = 0, p = 0;
			for (int v = 1; v < n; ++v) {
				if (v == m) continue;
				if (bit_set(mask, p++)) leftroute[l++] = v;
				else					rightroute[r++] = v; }

			ll lmin = LLINF, rmin = LLINF;
			do{ ll routelength = d[0][leftroute.empty() ? m : leftroute[0]];
				for (int i = 1; i < half; ++i)
					routelength += d[leftroute[i - 1]][leftroute[i]];
				if (!leftroute.empty())
					routelength += d[leftroute[half - 1]][m];
				lmin = min(lmin, routelength);
			} while (next_permutation(leftroute.begin(), leftroute.end()));

			do{ ll routelength = d[m][rightroute.empty() ? 0 : rightroute[0]];
				for (int i = 1; i < otherhalf; ++i)
					routelength += d[rightroute[i - 1]][rightroute[i]];
				if (!rightroute.empty())
					routelength += d[rightroute[otherhalf - 1]][0];
				rmin = min(rmin, routelength);
			} while (next_permutation(rightroute.begin(), rightroute.end()));

			shortest = min(shortest, lmin + rmin);

			if ((mask != 0)) {
				int lo = mask & ~(mask - 1);
				int lz = (mask + lo) & ~mask;
				mask |= lz;
				mask &= ~(lz - 1);
				mask |= (lz / lo / 2) - 1;
			} else break;
	}   }
	return shortest;
}