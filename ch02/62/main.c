#include <assert.h>

int int_shifts_are_arithmetic() {
    int int_bit_width = sizeof(int) << 3;

    // INT_MIN, most signifidcant bit is one and others are zero.
    int x = 1 << (int_bit_width-1);

    // Fully right shift and compare with -1 whose bit are all one.
    return (x >> (int_bit_width-1) == (int)-1);
}

int main() {
    // This machine uses an arithmetic right shift for data of int type.
    assert(int_shifts_are_arithmetic() == 1);
}
