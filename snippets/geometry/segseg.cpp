#include "../header.h"
bool intersect(P a1, P a2, P b1, P b2) {
	if (max(a1.x, a2.x) < min(b1.x, b2.x)) return false;
	if (max(b1.x, b2.x) < min(a1.x, a2.x)) return false;
	if (max(a1.y, a2.y) < min(b1.y, b2.y)) return false;
	if (max(b1.y, b2.y) < min(a1.y, a2.y)) return false;
	bool l1 = ccw(a2, b1, a1) * ccw(a2, b2, a1) <= 0;
	bool l2 = ccw(b2, a1, b1) * ccw(b2, a2, b1) <= 0;
	return l1 && l2;
}
