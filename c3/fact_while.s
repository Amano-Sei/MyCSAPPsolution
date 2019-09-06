	.file	"fact_while.c"
	.text
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB23:
	.cfi_startproc
	cmpq	$1, %rdi
	jle	.L4
	movl	$1, %eax
.L3:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jne	.L3
	rep ret
.L4:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	fact_while, .-fact_while
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
