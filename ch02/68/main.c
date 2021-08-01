#include <assert.h>

int lower_one_mask(int n) {
    // int のビット幅を *w* とする。すべてのビットを立てた数を
    // 用意し、その数に対し *w - n* 分論理右シフトをほどこす。
    // その結果が求めたい数となる。
    unsigned all_one = ~0;
    int int_size = sizeof(int) << 3;
    return all_one >> (int_size - n);
}

int main() {
    assert(lower_one_mask(1)  == 0x00000001);
    assert(lower_one_mask(6)  == 0x0000003F);
    assert(lower_one_mask(17) == 0x0001FFFF);
    assert(lower_one_mask(32) == 0xFFFFFFFF);
}
