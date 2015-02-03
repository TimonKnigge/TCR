ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound) {
    _sieve_size = upperbound + 1;
    bs.reset(); bs.flip();
    bs.set(0, false); bs.set(1, false);
    for (ll i = 2; i <= _sieve_size; ++i) {
        for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
        primes.push_back((int)i);
    }
}

bool is_prime(ll N) {    // Only works for N <= primes.last^2
    if (N < _sieve_size) return bs.test(N);
    for (int i = 0; i < primes.size(); ++i) if (N % primes[i] == 0) return false;
    return true;
}

vi prime_factors(int N) {
    int PFD_idx = 0, PF = primes[PF_idx]; vi factors;
    while (N != 1 && PF * PF <= N) {
        while (N % PF == 0) { N /= PF; factors.push_back(PF); }
        PF = primes[++PF_idx];
    }
    if (N != 1) factors.push_back(N);
    return factors;
}

ll totient(ll N) {
    vi factors = prime_factors(N);
    vi::iterator new_end = unique(factors.begin(), factors.end());
    ll result = N;
    for (vi::iterator i = factors.begin(); i != new_end; ++i) 
        result = result - result / (*i);
    return result;
}