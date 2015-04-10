typedef pair<ld, ld> cmpx;
cmpx cadd(cmpx lhs, cmpx rhs) {
    return cmpx(lhs.first + rhs.first, lhs.second + rhs.second);
}
cmpx csub(cmpx lhs, cmpx rhs) {
    return cmpx(lhs.first - rhs.first, lhs.second - rhs.second);
}
cmpx cmul(cmpx lhs, cmpx rhs) {
    return cmpx(lhs.first * rhs.first - lhs.second * rhs.second,
                lhs.first * rhs.second + lhs.second * lhs.first);
}
cmpx cdiv(cmpx lhs, cmpx rhs) {
    ld a = lhs.first, b = lhs.second,
       c = rhs.first, d = rhs.second;
    return cmpx((a * c + b * d) / (c * c + d * d),
                (b * c - a * d) / (c * c + d * d));
}
cmpx cexp(complex<ld> e) {
    e = exp(e);
    return cmpx(real(e), imag(e));
}
