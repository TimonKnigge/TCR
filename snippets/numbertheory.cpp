int gcd(int a, int b) { while (b) { a %= b; swap(a, b); } return a; }
int lcm(int a, int b) { return (a / gcd(a, b) * b);                 }
int mod(int a, int b) { return ((a % b) + b) % b;                   }

// Finds x, y s.t. ax + by = d = gcd(a, b).
void extendedEuclid(int a, int b, int &x, int &y, int &d) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    d = a;
}

// solves ab = 1 (mod n), -1 on failure
int modInverse(int a, int n) { 
    int x, y, d;
    extendedEuclid(a, n, x, y, d);
    return (d > 1 ? -1 : mod(x, n);
}

// Solve ax + by = c, returns false on failure.
bool linearDiophantine(int a, int b, int c, int &x, int &y) {
    int d = gcd(a, b);
    if (c % d) {
        return false;
    } else {
        x = c / d * modInverse(a / d, b / d);
        y = (c - a * x) / b;
        return true;
    }
}

// Chinese remainder theorem: finds z s.t. z % xi = ai. z is
// unique modulo M = lcm(xi). Returns (z, M), m = -1 on failure.
ii crm(int x1, int a1, int x2, int a2) {
    int s, t, d;
    extendedEuclid(x, y, s, t, d);
    if (a % d != b % d) return ii(0, -1);
    return ii(mod(s * a2 * x1 + t * a1 * x2, x1 * x2) / d, x1 * x2 / d);
}
ii crm(vi &x, vi &a){
    ii ret = ii(a[0], x[0]);
    for (int i = 1; i < x.size(); ++i) {
        ret = crm(ret.second, ret.first, x[i], a[i]);
        if (ret.second == -1) break;
    }
    return ret;
}