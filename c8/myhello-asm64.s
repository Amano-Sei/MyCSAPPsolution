.section .data
string:
    .ascii "ioridaisuki...\n"
string_end:
    .equ len, string_end - string
.section .text
.globl main
main:
    movq    $1, %rax
    movq    $1, %rdi
    movq    $string, %rsi
    movq    $len, %rdx
    syscall

    movq    $60, %rax
    movq    $0, %rdi
    syscall

# 然而并不知道怎么跑起来（
# 想想链接，好像也不像可以跑起来的样子...

