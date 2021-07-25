以下のコードを実行したところ、" 78 56 34 12" と出力された。
よってマシンのバイトオーダはリトルエンディアンである。

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

int main() {
    int x = 0x12345678;
    show_bytes((byte_pointer)&x, 4);
}
```
