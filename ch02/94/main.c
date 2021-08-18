#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned float_bits;

float float_twice_f(float f) {
    if (isnan(f))
        return f;
    else
        return f * 2.0;
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
    uint64_t bad = 0;
    uint64_t good = 0;

    unsigned x = 0;

    do {
        float *fp = (float *)&x;
        float f = float_twice_f(*fp);
        float_bits fb = float_twice(x);

        unsigned *ff = (unsigned *)&f;
        if (*ff != fb) {
            bad++;
            printf("%f (%.8x): %.8x != %.8x\n", *fp, x, fb, *ff);
        } else {
            good++;
        }
    } while (++x);

    printf("good=%lu, bad=%lu\n", good, bad);
}
