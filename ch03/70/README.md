### A

|member|offset|
|---|---|
|`e1.p`|0|
|`e1.y`|8|
|`e2.x`|0|
|`e2.next`|8|

### B

構造体 `e1` と `e2` はどちらも 16 バイトである。

### C

```x
void proc(union ele *up) {
    up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e2.next->x;
}
```

