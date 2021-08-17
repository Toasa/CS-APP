#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned float_bits;

float_bits f2u(float f) {
    return *(float_bits *)&f;
}

float u2f(float_bits u) {
    return *(float *)&u;
}

// Compute 2*f. If f is NaN, then return f.
float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f       & 0x7FFFFF;

    bool is_zero = (exp == 0)    && (frac == 0);
    bool is_nan  = (exp == 0xFF) && (frac != 0);
    bool is_inf  = (exp == 0xFF) && (frac == 0);

    if (is_zero || is_nan || is_inf)
        return f;

    if (exp == 0) {
        // Denormalized case
        // This shift works if it exceeds frac field.
        frac <<= 1;
    } else if (exp == 0xFE) {
        // A case of overflow if doubled. In that case, treat as infinite.
        // In fact, `FLT_MAX * 2 == INFINITY` is true in my environment.
        exp = 0xFF;
        frac = 0x0;
    } else {
        // Normalized case
        exp++;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    assert(u2f(float_twice(f2u(1.0)))     == 1.0 * 2);
    assert(u2f(float_twice(f2u(2.0)))     == 2.0 * 2);
    assert(u2f(float_twice(f2u(123.0)))   == 123.0 * 2);
    assert(u2f(float_twice(f2u(FLT_MAX))) == INFINITY);
}
