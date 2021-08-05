#include <assert.h>
#include <limits.h>

// Return 1 if x - y is not overflow, 0 otherwise.
int tsub_ok(int x, int y) {
    int pos_over = y < 0 && x > INT_MAX + y;
    int neg_over = y > 0 && x < INT_MIN + y;
    return !(pos_over || neg_over);
}

int main() {
    // Check positive overflow
    assert(tsub_ok(      1, INT_MIN) == 0);
    assert(tsub_ok(      0, INT_MIN) == 0);
    assert(tsub_ok(     -1, INT_MIN) == 1);
    assert(tsub_ok(INT_MAX,       1) == 1);
    assert(tsub_ok(INT_MAX,       0) == 1);
    assert(tsub_ok(INT_MAX,      -1) == 0);

    // Check negative overflow
    assert(tsub_ok(      0, INT_MAX) == 1);
    assert(tsub_ok(     -1, INT_MAX) == 1);
    assert(tsub_ok(     -2, INT_MAX) == 0);
    assert(tsub_ok(INT_MIN, INT_MAX) == 0);
}
