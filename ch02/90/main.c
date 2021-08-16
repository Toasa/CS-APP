#include <assert.h>
#include <math.h>

float u2f(unsigned x) {
    return *(float*)&x;
}

// return 2^x
float fpwr2(int x) {
    unsigned exp, frac;
    unsigned u;

    // Bias of float
    unsigned bias = 127;

    if (x < -149) {
        // Too small. Return 0.0
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        // Denormalized result
        exp = 0;
        frac = 1 << (x + 149);
    } else if (x < 128) {
        // Normalized result
        exp = x + bias;
        frac = 0;
    } else {
        // Too big. Return +oo
        exp = 0xFF;
        frac = 0;
    }

    // Pack exp and frac into 32 bits
    u = exp << 23 | frac;
    // Return as float
    return u2f(u);
}

int main() {
    assert(fpwr2(-150) == 0.0);
    assert(fpwr2(-128) == 2.938735877055719e-39);
    assert(fpwr2(  -5) == 0.03125);
    assert(fpwr2(   0) == 1.0);
    assert(fpwr2(  10) == 1024.0);
    assert(fpwr2( 128) == INFINITY);
}
