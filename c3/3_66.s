	.file	"3_66.c"
	.text
	.globl	sum_col
	.type	sum_col, @function
sum_col:
.LFB23:
	.cfi_startproc
	leaq	1(,%rdi,4), %r9
	leaq	(%rdi,%rdi,2), %r8
	movl	$0, %eax
	movl	$0, %ecx
	jmp	.L2
.L3:
	movq	%rcx, %rdi
	imulq	%r9, %rdi
	leaq	(%rsi,%rdi,8), %rdi
	addq	(%rdi,%rdx,8), %rax
	addq	$1, %rcx
.L2:
	cmpq	%r8, %rcx
	jl	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	sum_col, .-sum_col
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
