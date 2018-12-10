#include "../header.h"
void Z_algorithm(const string &s, vi &Z) {
	Z.assign(s.length(), -1);
	int L = 0, R = 0, n = s.length();
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else if (Z[i - L] >= R - i + 1) {
			L = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else Z[i] = Z[i - L];
	}
}
