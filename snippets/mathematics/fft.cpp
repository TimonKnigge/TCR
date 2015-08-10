#define MY_PI 3.14159265358979323846
#include "../header.h"
#include "../helpers/bitmasking.cpp"
#include "complex.cpp"

// A.size() = N = 2^p
void fft(vector<Complex>& A, int N, int p, bool inv = false) {
    for(int i = 0, r = 0; i < N; ++i, r = brinc(r, p))
        if (i < r) swap(A[i], A[r]);
    for (int m = 2; m <= N; m <<= 1) {
        Complex w, w_m = Complex::exp(complex<ld>(0, 2 * MY_PI / m * (inv ? -1 : 1)));
        for (int k = 0; k < N; k += m) {
            w = {1, 0};
            for (int j = 0; j < m / 2; ++j) {
                Complex t = w * A[k + j + m / 2];
                A[k + j + m / 2] = A[k + j] - t;
                A[k + j] = A[k + j] + t;
                w = w * w_m;
            }
        }
    }
    if (inv) for (int i = 0; i < N; ++i) {
        A[i].u /= N; A[i].v /= N;
    }
}

void convolution(vector<Complex>& A, vector<Complex>& B, vector<Complex>& C) {
    /// Pad with zeroes
    int N = 2 * max(next_power_of_2(A.size()), next_power_of_2(B.size()));
    A.reserve(N); B.reserve(N); C.reserve(N);
    for (int i = A.size(); i < N; ++i) A.push_back({0, 0});
    for (int i = B.size(); i < N; ++i) B.push_back({0, 0});
    int p = (int)round(log2(N));
    // Transform A and B
    fft(A, N, p, false);
    fft(B, N, p, false);
    // Calculate the convolution in C
    for (int i = 0; i < N; ++i) C.push_back(A[i] * B[i]);
    fft(C, N, p, true);
}
