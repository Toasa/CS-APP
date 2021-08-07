#include <assert.h>

int w = sizeof(int) << 3;

// x / (2^k)
// 0 <= k <= w
int divide_power2(int x, int k) {
    // lsb から 1 が k 個続いたマスク
    unsigned k_ones = ~((1 << (w-1)) >> (w - (1 + k)));

    // x >= 0 の場合は 0 を、x < 0 の場合は 1 が k 個続いた値を
    // bias とする。
    int bias = (x >> (w - 1)) & k_ones;

    return (x + bias) >> k;
}

int main() {
    assert(divide_power2(3,  1) == 1);
    assert(divide_power2(31, 2) == 7);

    assert(divide_power2(1024,   0) == 1024);
    assert(divide_power2(1024,   1) ==  512);
    assert(divide_power2(1024,  10) ==    1);
    assert(divide_power2(1024,  11) ==    0);
    assert(divide_power2(1024, w-1) ==    0);

    assert(divide_power2(-3,  1) == -1);
    assert(divide_power2(-31, 2) == -7);

    assert(divide_power2(-1024,   0) == -1024);
    assert(divide_power2(-1024,   1) ==  -512);
    assert(divide_power2(-1024,  10) ==    -1);
    assert(divide_power2(-1024,  11) ==     0);
    assert(divide_power2(-1024, w-1) ==     0);
}
