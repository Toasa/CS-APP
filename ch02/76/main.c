#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size) {
    if (nmemb > SIZE_MAX / size) {
        return NULL;
    }

    void *p = malloc(nmemb * size);
    return memset(p, 0, nmemb * size);
}

int main() {
    assert(my_calloc(1024,    10) != NULL);
    assert(my_calloc(SIZE_MAX, 2) == NULL);
}
