#include <assert.h>

int A(int x) {
    return !~x;
}

int B(int x) {
    return !x;
}

int C(int x) {
    // least significant byte
    unsigned char lsb = x & 0xFF;
    return !(unsigned char)~lsb;
}

int D(int x) {
    int int_bit_width = sizeof(int) << 3;
    // most significant byte
    unsigned char msb = (x >> (int_bit_width-8)) & 0xFF;
    return !msb;
}

int main() {
    assert(A(0x00000000) == 0);
    assert(A(0x00FF00FF) == 0);
    assert(A(0xFF00FF00) == 0);
    assert(A(0xFFFFFFFF) == 1);

    assert(B(0x00000000) == 1);
    assert(B(0x00FF00FF) == 0);
    assert(B(0xFF00FF00) == 0);
    assert(B(0xFFFFFFFF) == 0);

    assert(C(0x00000000) == 0);
    assert(C(0x00FF00FF) == 1);
    assert(C(0xFF00FF00) == 0);
    assert(C(0xFFFFFFFF) == 1);

    assert(D(0x00000000) == 1);
    assert(D(0x00FF00FF) == 1);
    assert(D(0xFF00FF00) == 0);
    assert(D(0xFFFFFFFF) == 0);
}
