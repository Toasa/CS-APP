### A

E = 0b01 - Bias, M = 0b1.11, f = 0b0.11, V = 7

ビット表現は以下：

```
0 10...01 110...0
  \     / \     /
     k       n
```

### B

E = n, M = 0b1.11..., f = 0b0.11..., V = 2^(n+1) - 1

ビット表現は以下：

```
0 (n+Bias) 11...11
  \      / \     /
     k        n
```

### C

E = Bias - 1, M = 0b1.00..., f = 0b0.00..., V = 2^(Bias - 1)

ビット表現は以下：

```
0 (2*Bias - 1) 00...00
  \          / \     /
        k         n
```
