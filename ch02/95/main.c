#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned float_bits;

float float_half_f(float f) {
    if (isnan(f))
        return f;
    else
        0.5 * f;
}

// Compute 0.5*f. If f is NaN, then return f.
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f       & 0x7FFFFF;

    bool is_zero = (exp == 0)    && (frac == 0);
    bool is_nan  = (exp == 0xFF) && (frac != 0);
    bool is_inf  = (exp == 0xFF) && (frac == 0);

    if (is_zero || is_nan || is_inf)
        return f;

    // Round to even
    //
    // We focus on the last two bits of the fraction field.
    // There are four cases (Y equals 1 or 0):
    //
    //   1. YYY00
    //   2. YYY01
    //   3. YYY10
    //   4. YYY11
    //
    // Now that we are considering a single right shift (because 0.5*f),
    // we need to round to even in the case of 2 and 4. So, the result
    // of a single right shift with rounding is as follows:
    //
    //   1. YYY0
    //   2. YYY0
    //   3. YYY1
    //   4. YYY1 + 1
    //
    // Therefore, we create a weight of +1 only in the case of 4.
    unsigned weight = ((frac & 0x3) == 0x3) ? 1 : 0;

    if (exp == 0) {
        // Denormalized case
        frac >>= 1;
        frac += weight;
    } else if (exp == 0x1) {
        // Normalized to denormalized.
        exp = 0;
        frac = ((exp << 23) | frac) >> 1;
        frac += weight;
    } else {
        // Normalized case
        exp--;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    uint64_t bad = 0;
    uint64_t good = 0;

    unsigned x = 0;

    do {
        float *fp = (float *)&x;
        float f = float_half_f(*fp);
        float_bits fb = float_half(x);

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
