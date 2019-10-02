	.file	"4_47.c"
	.text
	.globl	bubble_a
	.type	bubble_a, @function
bubble_a:
.LFB0:
	.cfi_startproc
	leaq	(%rdi,%rsi,8), %r9
	subq	$1, %rsi
	jmp	.L2
.L4:
	addq	$8, %rdx
	addq	$8, %rax
.L3:
	cmpq	%r9, %rax
	je	.L7
	movq	(%rdx), %r8
	movq	(%rax), %rcx
	cmpq	%rcx, %r8
	jle	.L4
	movq	%r8, (%rax)
	movq	%rcx, (%rdx)
	jmp	.L4
.L7:
	subq	$1, %rsi
.L2:
	testq	%rsi, %rsi
	jle	.L8
	leaq	8(%rdi), %rax
	movq	%rdi, %rdx
	jmp	.L3
.L8:
	rep ret
	.cfi_endproc
.LFE0:
	.size	bubble_a, .-bubble_a
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
