#include <assert.h>

// Declaration of data type where 4 bytes are packed into an unsigned
typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
    return (char)((word >> (bytenum << 3)) & 0xFF);
}

int main() {
    assert(xbyte(0x0000007F, 0) == 127);
    assert(xbyte(0x00007F00, 1) == 127);
    assert(xbyte(0x007F0000, 2) == 127);
    assert(xbyte(0x7F000000, 3) == 127);

    assert(xbyte(0x000000FF, 0) == -1);
    assert(xbyte(0x0000FF00, 1) == -1);
    assert(xbyte(0x00FF0000, 2) == -1);
    assert(xbyte(0xFF000000, 3) == -1);
}

