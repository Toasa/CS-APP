#include <assert.h>
#include <float.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned float_bits;

unsigned num_of_msb_digits(unsigned x) {
    int int_width = sizeof(int) << 3;
    for (int i = int_width - 1; i >= 0; i--) {
        if (((x >> i) & 1) == 1)
            return i;
    }

    // unreachable
    assert(0);
}

unsigned ones_mask(int i) {
    return 0xFFFFFFFF >> (32 - i);
}

float_bits float_i2f_f(int i) {
    float f = i;
    return *(float_bits *)&f;
}

float_bits float_i2f(int i) {
    unsigned sign = (i < 0) ? 1 : 0;
    unsigned exp;
    unsigned frac;
    unsigned bias = 127;

    if (i == 0) {
        exp = 0;
        frac = 0;
    } else if (i == INT_MIN) {
        exp = 31 + bias;
        frac = 0;
    } else {
        // Be positive
        if (i < 0)
            i *= -1;

        unsigned msb_digits = num_of_msb_digits(i);

        // Ignore implied leading one
        unsigned decimal_bit = ones_mask(msb_digits) & i;

        bool carried = false;

        if (msb_digits > 23) {
            // Round to even
            if (((decimal_bit >> (msb_digits - 24)) & 0x3) == 0x3) {
                decimal_bit += 1 << (msb_digits - 24);
            }

            if (ones_mask(msb_digits) < decimal_bit)
                carried = true;

            // If the fractional bit width of the binary fraction exceeds 23,
            // we have to consider a round up of fraction field. For exapmle,
            // suppose we round the rightmost Y in YYYXXX. If YYY001 or YYY100,
            // it is round down case and we get YYY. If YYY101 or YYY110, it is
            // round up case, then we get YYY + 1. Therefore, the threshold value
            // in this exapmle is 100.
            bool round_up = false;
            if ((ones_mask(msb_digits-23) & decimal_bit) > (1 << (msb_digits - 24)))
                round_up = true;

            frac = (decimal_bit >> (msb_digits - 23)) + (round_up ? 1 : 0);
        } else {
            frac = decimal_bit << (23 - msb_digits);
        }
        frac &= 0x7FFFFF;

        unsigned E = msb_digits;
        exp = E + bias + (carried ? 1 : 0);
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    uint64_t good = 0;
    uint64_t bad = 0;

    int x = 0;

    do {
        float_bits f = float_i2f_f(x);
        float_bits fi = float_i2f(x);

        if (f != fi) {
            bad++;
            printf("(%.8x): %.8x != %.8x\n", x, f, fi);
        } else {
            good++;
        }

    } while (++x);

    printf("good=%lu, bad=%lu\n", good, bad);
}
