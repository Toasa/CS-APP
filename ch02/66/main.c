#include <assert.h>

// Generate mask indicating leftmost 1 in x. Assume w=32.
// For exapmle 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
// If x = 0, then return 0.
int leftmost_one(unsigned x) {
    // 左端の 1 を起点に、それより右のすべてのビット
    // を 1 にする。
    x = x | (x>>1);
    x = x | (x>>2);
    x = x | (x>>4);
    x = x | (x>>8);
    x = x | (x>>16);

    return x - (x>>1);
}

int main() {
    assert(leftmost_one(0x00000000) == 0x00000000);
    assert(leftmost_one(0x00001100) == 0x00001000);
    assert(leftmost_one(0x00003300) == 0x00002000);
    assert(leftmost_one(0x00006600) == 0x00004000);
    assert(leftmost_one(0x0000FF00) == 0x00008000);
    assert(leftmost_one(0x1FFFFFFF) == 0x10000000);
    assert(leftmost_one(0x2FFFFFFF) == 0x20000000);
    assert(leftmost_one(0x7FFFFFFF) == 0x40000000);
    assert(leftmost_one(0xEFFFFFFF) == 0x80000000);
    assert(leftmost_one(0xFFFFFFFF) == 0x80000000);
}
