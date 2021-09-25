```c
if (Fork() == 0) {
    dup2(0, 3);
    Execve("fstackcheck", argv, envp);
}
```
