#include <assert.h>

int int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main() {
    assert(int_size_is_32() == 1);
}
