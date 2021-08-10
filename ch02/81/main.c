#include <assert.h>

int w = sizeof(int) << 3;

// 11...1100...00
// \     /\     /
//   w-k     k
unsigned A(unsigned k) {
    // k の取りうる範囲は 0 <= k <= w となる。

    if (k == 0)
        return 0;
    
    // 以降は k >= 1 と仮定できる。
    // 最上位ビットのみ 1 である数を作成し、その数に対し
    // k - 1 の算術右シフトを行うことで求めたい数となる。
    int msb_only = ~(~(unsigned)0 >> 1);
    return msb_only >> (k - 1);
}

// 00...0011...1100...00
// \     /\     /\     /
//  w-k-j    k      j
unsigned B(unsigned j, unsigned k) {
    // k の取りうる範囲は 0 <= k+j <= w となる。
    if (k == 0)
        return 0;

    return ((1 << (k + j)) - 1) - ((1 << j) - 1);
}

int main() {
    assert(A(0)  == 0x00000000);
    assert(A(1)  == 0x80000000);
    assert(A(2)  == 0xC0000000);
    assert(A(4)  == 0xF0000000);
    assert(A(16) == 0xFFFF0000);
    assert(A(31) == 0xFFFFFFFE);
    assert(A(32) == 0xFFFFFFFF);

    assert(B(0, 0) == 0x00000000);
    assert(B(1, 0) == 0x00000000);
    assert(B(0, 1) == 0x00000001);
    assert(B(1, 1) == 0x00000002);
    assert(B(8, 1) == 0x00000100);
    assert(B(8, 2) == 0x00000300);
    assert(B(8, 4) == 0x00000F00);
    assert(B(8,16) == 0x00FFFF00);
}
