	.file	"3_65.c"
	.text
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB23:
	.cfi_startproc
	leaq	120(%rdi), %r10
	movl	$0, %r9d
	jmp	.L2
.L5:
	leaq	(%rdi,%r9,8), %rax
	movq	%r9, %r8
	salq	$7, %r8
	addq	%rdi, %r8
	movq	%r10, %rdx
.L3:
	movq	(%rdx), %rcx
	movq	(%rax), %rsi
	movq	%rsi, (%rdx)
	movq	%rcx, (%rax)
	addq	$8, %rdx
	addq	$120, %rax
	cmpq	%r8, %rax
	jne	.L3
.L6:
	addq	$120, %r10
.L2:
	addq	$1, %r9
	cmpq	$15, %r9
	je	.L1
	testq	%r9, %r9
	jg	.L5
	jmp	.L6
.L1:
	rep ret
	.cfi_endproc
.LFE23:
	.size	transpose, .-transpose
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
