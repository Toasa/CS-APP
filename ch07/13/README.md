### A

`libc.a` のオブジェクトファイル数は以下のコマンドで確かめた：

```
$ ar t /usr/lib/x86_64-linux-gnu/libc.a | wc -l // 1740
```

`libm.a` は ld command language で以下のようにグルーピングされていた:

```
GROUP ( /usr/lib/x86_64-linux-gnu/libm-2.31.a /usr/lib/x86_64-linux-gnu/libmvec.a )
```

そのため `libm-2.31.a` と `libmvec.a` それぞれに対し、オブジェクトファイルの数を求めた：

```
$ ar t /usr/lib/x86_64-linux-gnu/libm-2.31.a | wc -l // 802
$ ar t /usr/lib/x86_64-linux-gnu/libmvec.a | wc -l   // 128
```

### B

`-Og` と `-Og -g` とはセクションヘッダの数が違った。後者の方が以下の 5 つ多かった.

- `.debug_aranges`
- `.debug_info`
- `.debug_abbrev`
- `.debug_line`
- `.debug_str`

以下の diff コマンドで確かめた:

```
$ diff -u <(objdump -h main_og) <(objdump -h main_ogg)
```

### C

`ldd` コマンドで確かめた。以下の３つの共有ライブラリを利用していた：

```
$ ldd /usr/bin/gcc
	linux-vdso.so.1 (0x00007ffed0dfc000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f58749c0000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f5874bc9000)
```
