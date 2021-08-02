#include <assert.h>

unsigned rotate_left(unsigned x, int n) {
    int int_width = sizeof(int) << 3;
    unsigned shifted = x << n;
    unsigned rotated = x >> (int_width - n);
    return shifted | rotated;
}

int main() {
    assert(rotate_left(0x12345678,  0) == 0x12345678);
    assert(rotate_left(0x12345678,  1) == 0x2468acf0);
    assert(rotate_left(0x12345678,  4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    assert(rotate_left(0x12345678, 31) == 0x091A2B3C);
}
