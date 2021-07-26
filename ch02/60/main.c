#include <assert.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    if (i < 0 || 3 < i) {
        fprintf(stderr, "Shift count must be from 0 to 3, but got %d\n", i);
        return 0;
    }

    // Create mask whose i th byte is zero, others are one.
    // (ex. i equals 1, then mask is 0xFFFF00FF)
    unsigned mask = ~(0xFF << (i << 3));

    return ((x & mask) | b << (i << 3));
}

int main() {
    assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
    assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);

    assert(replace_byte(0x12345678, -1, 0xAB) == 0);
    assert(replace_byte(0x12345678, 4, 0xAB) == 0);
}
