#include <stdio.h>

#define ARR_SIZE(A) sizeof(A) / sizeof(A[0])

unsigned int f(unsigned int x, unsigned int y) {
    return (x & 0xFF) | (y & 0xFFFFFF00);
}

struct Test {
    unsigned int x; // operand 1
    unsigned int y; // operand 2
    unsigned int e; // expected
};

void do_tests() {
    struct Test tests[] = {
        {
            .x = 0x00000000,
            .y = 0xFFFFFFFF,
            .e = 0xFFFFFF00,
        },
        {
            .x = 0xFFFFFFFF,
            .y = 0x00000000,
            .e = 0x000000FF,
        }
    };

    for (int i = 0; i < ARR_SIZE(tests); i++) {
        struct Test t = tests[i];
        unsigned int ret = f(t.x, t.y);
        if (ret != t.e) {
            printf("Expected 0x%04X, but got 0x%04X\n", t.e, ret);
            return;
        }
    }
    printf("OK\n");
}

int main() {
    do_tests();
}
