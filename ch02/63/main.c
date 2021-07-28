#include <stdio.h>
#include <limits.h>
#include <assert.h>

void printb(unsigned int v) {
    unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);

    int count = 0;
    do {
        putchar(mask & v ? '1' : '0');
        count++;
        if (count == 8 || count == 16 || count == 24)
            putchar('_');
    } while (mask >>= 1);

    printf("\n");
}

// Bit width of int
static int w = 8 * sizeof(int);

unsigned srl(unsigned x, int k) {
    // Perform shift arithmetically
    unsigned xsra = (int) x >> k;

    // `k` zeros follow from the most significant bit, others are ones.
    //
    //     00..0011...11
    //     \    /\     /
    //       k     w-k
    //
    unsigned mask = ((unsigned long)1 << (w - k)) - 1;

    return xsra & mask;
}

unsigned sra(unsigned x, int k) {
    // Perform shift logically
    int xsrl = (unsigned) x >> k;

    // `(w-(k+1))`th bit is only one, others are zeros.
    unsigned mask = 1 << (w - (k+1));

    // Basic idea is in "Hacker's delight, Ch.2-7". The subtraction
    // has effect of lining up ones if the msb is one.
    return (xsrl ^ mask) - mask;
}

int main() {
    assert(srl(0xFF000000, 0)  == 0xFF000000);
    assert(srl(0xFF000000, 4)  == 0x0FF00000);
    assert(srl(0xFF000000, 8)  == 0x00FF0000);
    assert(srl(0xFF000000, 24) == 0x000000FF);
    assert(srl(0xFF000000, 31) == 0x00000001);
    assert(srl(0x00FF0000, 4)  == 0x000FF000);
    assert(srl(0x00FF0000, 8)  == 0x0000FF00);
    assert(srl(0x00FF0000, 24) == 0x00000000);
    assert(srl(0x00FF0000, 31) == 0x00000000);

    assert(sra(0xFF000000, 0)  == 0xFF000000);
    assert(sra(0xFF000000, 4)  == 0xFFF00000);
    assert(sra(0xFF000000, 8)  == 0xFFFF0000);
    assert(sra(0xFF000000, 24) == 0xFFFFFFFF);
    assert(sra(0xFF000000, 31) == 0xFFFFFFFF);
    assert(sra(0x00FF0000, 4)  == 0x000FF000);
    assert(sra(0x00FF0000, 8)  == 0x0000FF00);
    assert(sra(0x00FF0000, 24) == 0x00000000);
    assert(sra(0x00FF0000, 31) == 0x00000000);
}
