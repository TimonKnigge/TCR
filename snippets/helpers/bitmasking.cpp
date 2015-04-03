#ifdef _MSC_VER
#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcount(x)
#endif

bool bit_set(int mask, int pos) {
    return ((mask & (1 << pos)) != 0);
}

// Iterate over all subsets of a set of size N
for (int mask = 0; mask < (1 << N); ++mask) {
    // Decode mask here
}

// Iterate over all k-subsets of a set of size N
int mask = (1 << k) - 1;
while (!(mask & 1 << N)) {
    // Decode mask here
    int lo = mask & ~(mask - 1);
    int lz = (mask + lo) & ~mask;
    mask |= lz;
    mask &= ~(lz - 1);
    mask |= (lz / lo / 2) - 1;
}

// Iterate over all subsets of a subset
int mask = givenMask;
do {
    // Decode mask here
    mask = (mask - 1) & givenMask;
} while (mask != givenMask);

// The two functions below are used in the FFT:
inline int next_power_of_2(int x) {
    x--; x |= x >> 1;
    x |= x >> 2; x |= x >> 4;
    x |= x >> 8; x |= x >> 16;
    x++; return x;
}

inline int nbit_reverse(int x, int n) {
    for (int i = 0, d = n - 1; i < n / 2; ++i, d -= 2) {
        int l = (x & (1 << i)), r = (x & (1 << (n - 1 - i)));
        x ^= (l << d ^ r) | (r >> d ^ l);
    }
    return x;
}