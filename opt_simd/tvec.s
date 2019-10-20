	.file	"tvec.c"
	.text
	.globl	innerv
	.type	innerv, @function
innerv:
.LFB23:
	.cfi_startproc
	subq	$192, %rsp
	.cfi_def_cfa_offset 200
	vmovdqa	200(%rsp), %ymm0
	vpmulld	264(%rsp), %ymm0, %ymm0
	vmovaps	%xmm0, -72(%rsp)
	movq	-72(%rsp), %rsi
	movq	-64(%rsp), %rdi
	vmovdqa	%ymm0, -56(%rsp)
	vmovdqa	232(%rsp), %ymm0
	vpmulld	296(%rsp), %ymm0, %ymm0
	vmovaps	%xmm0, -72(%rsp)
	movq	-72(%rsp), %rax
	movq	-64(%rsp), %rdx
	vmovdqa	%ymm0, -24(%rsp)
	movq	%rsi, 72(%rsp)
	movq	%rdi, 80(%rsp)
	vmovdqa	-40(%rsp), %xmm1
	vmovaps	%xmm1, 88(%rsp)
	movq	%rax, 104(%rsp)
	movq	%rdx, 112(%rsp)
	movq	-8(%rsp), %r9
	movq	(%rsp), %r10
	movq	%r9, 120(%rsp)
	movq	%r10, 128(%rsp)
	movq	%rsi, 8(%rsp)
	movq	%rdi, 16(%rsp)
	vmovaps	%xmm1, 24(%rsp)
	movq	%rax, 40(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%r9, 56(%rsp)
	movq	%r10, 64(%rsp)
	movl	$0, %eax
	movl	$0, %edx
	jmp	.L2
.L3:
	addl	8(%rsp,%rdx,4), %eax
	addq	$1, %rdx
.L2:
	cmpq	$15, %rdx
	jbe	.L3
	addq	$192, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	innerv, .-innerv
	.globl	tmov
	.type	tmov, @function
tmov:
.LFB24:
	.cfi_startproc
	movq	$0, 16(%rdi)
	movq	$0, 24(%rdi)
	movq	$0, 32(%rdi)
	movq	$0, 40(%rdi)
	movq	$0, 48(%rdi)
	movq	$0, 56(%rdi)
	movl	$1, (%rdi)
	movl	$1, 4(%rdi)
	movl	$1, 8(%rdi)
	movl	$1, 12(%rdi)
	ret
	.cfi_endproc
.LFE24:
	.size	tmov, .-tmov
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
