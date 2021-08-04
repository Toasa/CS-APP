#include <assert.h>
#include <stdbool.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes - (int)sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}

bool is_all_zero(char *buf, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (buf[i] != 0)
            return false;
    }
    return true;
}

int main() {
    char buf1[4] = {};
    copy_int(1, buf1, sizeof(buf1));
    assert(!is_all_zero(buf1, sizeof(buf1)));

    char buf2[3] = {};
    copy_int(1, buf2, sizeof(buf2));
    assert(is_all_zero(buf2, sizeof(buf2)));
}
