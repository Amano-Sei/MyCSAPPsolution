	.file	"3_69.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB23:
	.cfi_startproc
	movl	288(%rsi), %edx
	addl	(%rsi), %edx
	leaq	0(,%rdi,4), %rax
	leaq	(%rax,%rdi), %r8
	leaq	0(,%r8,8), %rcx
	addq	%rdi, %rax
	addq	8(%rsi,%rcx), %rax
	movslq	%edx, %rdx
	movq	%rdx, 16(%rsi,%rax,8)
	ret
	.cfi_endproc
.LFE23:
	.size	test, .-test
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
