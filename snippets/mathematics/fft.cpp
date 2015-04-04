#define MY_PI 3.14159265358979323846

// A.size() = N = 2^p
void fft(vector<cmpx>& A, int N, int p, bool inv = false) {
    for(int i = 0, r = 0; i < N; ++i, r = nbit_reverse(i, p))
        if (i < r) swap(A[i], A[r]);
    for (int m = 2; m <= N; m <<= 1) {
        cmpx w_m = cexp(complex<ld>(0, 2 * MY_PI / m * (inv ? -1 : 1))), w;
        for (int k = 0; k < N; k += m) {
            w = cmpx(1, 0);
            for (int j = 0; j < m / 2; ++j) {
                cmpx t = cmul(w, A[k + j + m / 2]);
                A[k + j + m / 2] = csub(A[k + j], t);
                A[k + j] = cadd(A[k + j], t);
                w = cmul(w, w_m);
            }
        }
    }
    if (inv) for (int i = 0; i < N; ++i) {
        A[i].first /= N; A[i].second /= N;
    }
}

void convolution(vector<cmpx>& A, vector<cmpx>& B, vector<cmpx>& C) {
    /// Pad with zeroes
    int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
    A.reserve(N); B.reserve(N); C.reserve(N);
    for (int i = A.size(); i < N; ++i) A.push_back(0);
    for (int i = B.size(); i < N; ++i) B.push_back(0);
    int p = (int)round(log2(N));
    // Transform A and B
    fft(A, N, p, false);
    fft(B, N, p, false);
    // Calculate the convolution in C
    for (int i = 0; i < N; ++i) C.push_back(cmul(A[i], B[i]));
    fft(C, N, p, true);
}