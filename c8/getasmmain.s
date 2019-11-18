	.file	"getasmmain.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
    movq    $1, %rax
    movq    $1, %rdi
    leaq    thestring(%rip), %rsi
    movq    len(%rip), %rdx
    syscall

    movq    $60, %rax
    movq    $0, %rdi
    syscall
# 现实是打印并没有出现（
# 然而其实是我一开始蠢忘记用leaq（（（
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	len
	.data
	.align 4
	.type	len, @object
	.size	len, 4
len:
	.long	15
	.globl	thestring
	.align 16
	.type	thestring, @object
	.size	thestring, 16
thestring:
	.ascii	"ioridaisuki...\n"
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
