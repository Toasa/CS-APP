#include <math.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned float_bits;

float float_absval_f(float f) {
    if (isnan(f))
        return f;
    else
        return fabs(f);
}

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

int main() {
    uint64_t bad = 0;
    uint64_t good = 0;

    unsigned x = 0;

    do {
        float *fp = (float *)&x;
        float f = float_absval_f(*fp);
        float_bits fb = float_absval(x);

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
