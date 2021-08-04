usual arithmetic conversion により、`int` と `unsigned int` 
の二項演算は `unsigned int` 同士の演算に変換される。よって
`if` の条件式 `maxbytes-sizeof(val)` は常に 0 以上の整数と
なる。
