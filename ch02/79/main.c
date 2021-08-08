#include <assert.h>
#include <limits.h>

int w = sizeof(int) << 3;

int mul3div4(int x) {
    int mul3 = (x << 1) + x;

    // x >= 0 の場合は 0 を、x < 0 の場合は 0b11 をbias とする
    int bias = (x >> (w - 1)) & 0b11;

    return (mul3 + bias) >> 2;
}

int main() {
    assert(mul3div4(10)      ==      10 * 3 / 4);
    assert(mul3div4(15)      ==      15 * 3 / 4);
    assert(mul3div4(-5)      ==      -5 * 3 / 4);
    assert(mul3div4(INT_MAX) == INT_MAX * 3 / 4);
    assert(mul3div4(INT_MIN) == INT_MIN * 3 / 4);
}
