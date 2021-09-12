cread_alt:
    movq   0, %rax
    testq  %rdi, %rdi
    cmovne (%rdi), %rax
    ret
