#include <float.h>
#include <limits.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_short(short x) {
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
    show_bytes((byte_pointer) &x, sizeof(double));
}

int main() {
    show_short(SHRT_MAX);
    show_short(SHRT_MIN);

    show_long(LONG_MAX);
    show_long(LONG_MIN);

    show_double(DBL_MAX);
    show_double(DBL_MIN);
}
