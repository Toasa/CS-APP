#include <assert.h>

// Return 1 when any odd bit of x equals 1; 0 otherwise.
// Assume w=32
int any_odd_one(unsigned x) {
    // 01010101...0101
    unsigned mask = 0x55555555;
    return (mask & x) == mask;
}

int main() {
    assert(any_odd_one(0x00000000) == 0);
    assert(any_odd_one(0x00005555) == 0);
    assert(any_odd_one(0x11111111) == 0);
    assert(any_odd_one(0x44444444) == 0);
    assert(any_odd_one(0x55555555) == 1);
    assert(any_odd_one(0x77777777) == 1);
    assert(any_odd_one(0xDDDDDDDD) == 1);
    assert(any_odd_one(0xFFFFFFFF) == 1);
}
