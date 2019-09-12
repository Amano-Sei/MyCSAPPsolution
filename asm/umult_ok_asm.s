.globl umult_ok_asm
# int umult_ok_asm(unsigned long x, unsigned long y, unsigned long *dest)
# x in %rdi, y in %rsi, dest in %rdx
umult_ok_asm:
    movq    %rdx, %rcx
    movq    %rsi, %rax
    mulq    %rdi
    movq    %rax, (%rcx)
    setae   %al
    movzbl  %al, %eax
    ret

