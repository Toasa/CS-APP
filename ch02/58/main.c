#include <stdbool.h>
#include <stdio.h>

bool is_little_endian() {
    short x = 1;
    char *p = (char *)&x;
    return *p == 1;
}

int main() {
    printf("little endian?: %s\n", is_little_endian() ? "true" : "false");
}

