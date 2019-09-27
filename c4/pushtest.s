    .text
.globl pushtest
pushtest:
    movq    %rsp, %rax
    pushq   %rsp
    popq    %rdx
    subq    %rdx, %rax
    ret

