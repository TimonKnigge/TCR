from math import floor
from fractions import Fraction
F, fl = Fraction, floor
cf = lambda f: [fl(f)] + ([] if not f-fl(f) else cf(1 / (f - fl(f))))
icf = lambda l: F(l[0]) if len(l) == 1 else l[0] + 1 / icf(l[1:])
approx = lambda f, c: f.limit_denominator(c)

# Takes two continued fractions in list form, and returns a continued
# fraction in (l, r) that has smallest numerator and denominator possible.
def lwithin(l, r):
    if len(r) == 0 or r[0] > l[0] + int(len(r) == 1): return [l[0]+1]
    if l[0]+1 == r[0]: r = [r[0]-1, 1]
    return [l[0]] + lwithin(r[1:], l[1:])

def cmp(l, r):
	if not r or not l or l[0] < r[0]: return bool(r)
	return cmp(r[1:], l[1:])
