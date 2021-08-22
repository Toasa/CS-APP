#include <float.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned float_bits;

int float_f2i_f(float_bits fb) {
    float f = *(float *)&fb;
    if (isnan(f))
        return 0x80000000;

    return (int)f;
}

int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f       & 0x7FFFFF;
    unsigned bias = 127;

    int val;
    if (exp < 0 + bias)
        val = 0;
    else if (exp >= 31 + bias)
        // overflow
        val = 0x80000000;
    else {
        // Activate a implied leading one.
        frac |= 0x800000;
        int E = exp - bias;
        if (E >= 23)
            val = frac << (E - 23);
        else
            val = frac >> (23 - E);
    }

    return sign ? -val : val;
}

int main() {
    uint64_t good = 0;
    uint64_t bad = 0;

    unsigned x = 0;

    do {
        int i = float_f2i_f(x);
        int fi = float_f2i(x);

        if (i != fi) {
            bad++;
            printf("(%.8x): %.8x != %.8x\n", x, i, fi);
        } else {
            good++;
        }
    } while (++x);

    printf("good=%lu, bad=%lu\n", good, bad);
}
