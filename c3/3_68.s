	.file	"3_68.c"
	.text
	.globl	setVal
	.type	setVal, @function
setVal:
.LFB23:
	.cfi_startproc
	movslq	8(%rsi), %rax
	addq	32(%rsi), %rax
	movq	%rax, 184(%rdi)
	ret
	.cfi_endproc
.LFE23:
	.size	setVal, .-setVal
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
