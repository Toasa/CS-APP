#include <assert.h>

// Return 1 when x contains an odd number of 1s; 0 otherwise.
// Assume w=32
int odd_ones(unsigned x) {
    // 分割統治法を使う。まず 32 bit を 2 bit ずつに区切り、
    // その区間内で 1 の個数が偶数個であれば 0 を、奇数個で
    // あれば 1 をその区間に記録する。
    x = (x>>1) ^ x;

    // 次に 4 bit の区間において、1 の個数の偶奇性を調べる。
    // このとき記録された前の結果が使えるため、前の bit 幅分
    // シフトし、xor で求める。求めた偶奇性を 4 bit 区間に
    // 記録する。以降 16 bit の区間まで同様の操作を続ける。
    x = (x>>2) ^ x;
    x = (x>>4) ^ x;
    x = (x>>8) ^ x;
    x = (x>>16) ^ x;

    // x の lsb に求めたい偶奇性が記録されているため、mask 
    // を使い取り出す。
    return x & 0x1;
}

int main() {
    assert(odd_ones(0x00000000) == 0);
    assert(odd_ones(0x00000001) == 1);
    assert(odd_ones(0x00000011) == 0);
    assert(odd_ones(0x00000111) == 1);
    assert(odd_ones(0x00001111) == 0);
    assert(odd_ones(0x00011111) == 1);
    assert(odd_ones(0x00111111) == 0);
    assert(odd_ones(0x01111111) == 1);
    assert(odd_ones(0x11111111) == 0);
    assert(odd_ones(0x11111110) == 1);
    assert(odd_ones(0x11111100) == 0);
    assert(odd_ones(0x11111000) == 1);
    assert(odd_ones(0x11110000) == 0);
    assert(odd_ones(0x11100000) == 1);
    assert(odd_ones(0x11000000) == 0);
    assert(odd_ones(0x10000000) == 1);

    assert(odd_ones(0x10101010) == 0);
    assert(odd_ones(0x01010101) == 0);
    assert(odd_ones(0x01000101) == 1);
    assert(odd_ones(0x01010111) == 1);

    assert(odd_ones(0xFFFEFFFE) == 0);
    assert(odd_ones(0xFFFFFFEE) == 0);
    assert(odd_ones(0xFFFFFFFE) == 1);
    assert(odd_ones(0xFFFFFFFF) == 0);
}
