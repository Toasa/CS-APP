#include <assert.h>
#include <limits.h>

int fits_bits(int x, int n) {
    // `n` ビットの 2 の補数表現で表現可能な整数 (*x* とする) は、
    // `n` ビットの符号なし整数で表現可能な整数 (*ux* とする) と
    // 1 対 1 に対応する。この対応は
    //   ux := x + 2 ^ (n - 1)
    // により得られる。よって *x* が `n` ビットの 2 の補数表現で
    // 表現可能であることは、*ux* が `n` ビットの符号なし整数で
    // あることをチェックすれば良い。このチェックは `ux` の `n`
    // ビット目以上が 0 であることを確かめれば良い。

    unsigned ux = x + (1 << (n - 1));

    int int_width = sizeof(int) << 3;
    // lsb から 1 が n 個続いたマスク
    unsigned n_ones = (unsigned)(~0) >> (int_width - n);

    return (ux | n_ones) == n_ones;
}

int main() {
    assert(fits_bits(-2, 1) == 0);
    assert(fits_bits(-1, 1) == 1);
    assert(fits_bits( 0, 1) == 1);
    assert(fits_bits( 1, 1) == 0);

    assert(fits_bits(-3, 2) == 0);
    assert(fits_bits(-2, 2) == 1);
    assert(fits_bits(-1, 2) == 1);
    assert(fits_bits( 0, 2) == 1);
    assert(fits_bits( 1, 2) == 1);
    assert(fits_bits( 2, 2) == 0);

    assert(fits_bits(INT_MIN, 31) == 0);
    assert(fits_bits(-3,      31) == 1);
    assert(fits_bits(-2,      31) == 1);
    assert(fits_bits(-1,      31) == 1);
    assert(fits_bits( 0,      31) == 1);
    assert(fits_bits( 1,      31) == 1);
    assert(fits_bits( 2,      31) == 1);
    assert(fits_bits(INT_MAX, 31) == 0);

    assert(fits_bits(INT_MIN, 32) == 1);
    assert(fits_bits(-3,      32) == 1);
    assert(fits_bits(-2,      32) == 1);
    assert(fits_bits(-1,      32) == 1);
    assert(fits_bits( 0,      32) == 1);
    assert(fits_bits( 1,      32) == 1);
    assert(fits_bits( 2,      32) == 1);
    assert(fits_bits(INT_MAX, 32) == 1);
}
