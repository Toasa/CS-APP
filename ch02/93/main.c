typedef unsigned float_bits;

// Compute |f|. If f is NaN, then return f.
float_bits float_absval(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f       & 0x7FFFFF;

    // NaN case
    if (exp == 0xFF && frac != 0) {
        return f;
    }

    // Be positive
    sign = 0;

    return (sign << 31) | (exp << 23) | frac;
}
