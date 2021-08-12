#include <assert.h>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    // Get the sign bits
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    if (sx == 0 && sy == 0)
        return ux <= uy;
    else if (sx == 1 && sy == 1)
        return ux >= uy;
    else if (sx == 1 && sy == 0)
        return 1;
    else if (sx == 0 && sy == 1)
        return ((0x7FFFFFFF & ux) == 0) && ((0x7FFFFFFF & uy) == 0) ? 1 : 0;

    // unreachable
    assert(0);
}

int main() {
    assert(float_le(+0.0, -0.0) == 1);

    assert(float_le(0.0,   1.0) == 1);
    assert(float_le(1.0,   1.1) == 1);
    assert(float_le(-1.0,  0.0) == 1);
    assert(float_le(-1.0,  1.0) == 1);
    assert(float_le(-0.0,  1.0) == 1);
    assert(float_le(-1.0, -0.9) == 1);

    assert(float_le(1.0,   0.0) == 0);
    assert(float_le(1.0,   0.5) == 0);
    assert(float_le(-1.0, -2.5) == 0);
    assert(float_le(1.0,  -2.5) == 0);
}
