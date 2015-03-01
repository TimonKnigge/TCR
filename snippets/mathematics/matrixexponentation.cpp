#define ITERATE_MATRIX(w) for (int r = 0; r < (w); ++r) \
                          for (int c = 0; c < (w); ++c)
template <class T, int N>
struct Matrix {
    T m[N][N];
    Matrix() { ITERATE_MATRIX(N) m[c][r] = 0; }
    Matrix(Matrix& o) { ITERATE_MATRIX(N) m[c][r] = o.m[c][r]; }
    static Matrix<T, N> identity() {
        Matrix<T, N> I;
        for (int i = 0; i < N; ++i) I.m[i][i] = 1;
        return I;
    }
    static Matrix<T, N> multiply(Matrix<T, N> lhs, Matrix<T, N> rhs) {
        Matrix<T, N> out;
        ITERATE_MATRIX(N)
            for (int i = 0; i < N; ++i)
                out.m[c][r] += lhs.m[i][r] * rhs.m[c][i];
        return out;
    }
    Matrix<T, N> raise(int n) {
        if (n == 0) return Matrix<T, N>::identity();
        if (n == 1) return Matrix<T, N>(*this);
        if (n == 2) return Matrix<T, N>::multiply(*this, *this);
        if (n % 2 == 0)
            return Matrix<T, N>::multiply(*this, *this).raise(n / 2);
        return Matrix<T, N>::multiply(*this,
            Matrix<T, N>::multiply(*this, *this).raise((n - 1) / 2));
    }
};