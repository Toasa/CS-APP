#include <assert.h>

int mul_17(int x) {
    return (x << 4) + x;
}

int mul_m7(int x) {
    return x - (x << 3);
}

int mul_60(int x) {
    return (x << 6) - (x << 2);
}

int mul_m112(int x) {
    return (x << 4) - (x << 7);
}

int main() {
    assert(mul_17(10) == 10 * 17);
    assert(mul_17(-2) == -2 * 17);

    assert(mul_m7(-2) == -2 * -7);
    assert(mul_m7(12) == 12 * -7);

    assert(mul_60(55) == 55 * 60);
    assert(mul_60(-8) == -8 * 60);

    assert(mul_m112(12) == 12 * -112);
    assert(mul_m112(-7) == -7 * -112);
}
