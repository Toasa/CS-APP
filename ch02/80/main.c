#include <assert.h>
#include <limits.h>

int w = sizeof(int) << 3;

int threefourths(int x) {
    // x >= 0 の場合は 0 を、x < 0 の場合は 0b11 をbias とする。
    int bias = (x >> (w - 1)) & 0b11;

    // オーバーフローを防ぐため、はじめに 4 で割り、
    // その後 3 を掛ける。
    int div4 = (x + bias) >> 2;
    return (div4 << 1) + div4;
}

int main() {
    assert(threefourths(10)      ==      10 / 4 * 3);
    assert(threefourths(15)      ==      15 / 4 * 3);
    assert(threefourths(-5)      ==      -5 / 4 * 3);
    assert(threefourths(INT_MAX) == INT_MAX / 4 * 3);
    assert(threefourths(INT_MIN) == INT_MIN / 4 * 3);
}
