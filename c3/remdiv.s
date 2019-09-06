	.file	"remdiv.c"
	.text
	.globl	remdiv
	.type	remdiv, @function
remdiv:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	movq	%rdx, %rdi
	cqto
	idivq	%rsi
	movq	%rax, (%rdi)
	movq	%rdx, (%rcx)
	ret
	.cfi_endproc
.LFE23:
	.size	remdiv, .-remdiv
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
