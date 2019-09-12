	.file	"3_67.c"
	.text
	.globl	process
	.type	process, @function
process:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	movq	16(%rsp), %rdx
	movq	%rdx, (%rdi)
	movq	8(%rsp), %rdx
	movq	%rdx, 8(%rdi)
	movq	24(%rsp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, 16(%rdi)
	ret
	.cfi_endproc
.LFE23:
	.size	process, .-process
	.globl	eval
	.type	eval, @function
eval:
.LFB24:
	.cfi_startproc
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	movq	%rdx, (%rsp)
	movq	%rsi, 48(%rsp)
	movq	%rsp, %rax
	movq	%rax, 56(%rsp)
	leaq	8(%rsp), %rax
	pushq	56(%rsp)
	.cfi_def_cfa_offset 88
	pushq	56(%rsp)
	.cfi_def_cfa_offset 96
	pushq	%rdi
	.cfi_def_cfa_offset 104
	movq	%rax, %rdi
	call	process
	movq	40(%rsp), %rax
	addq	32(%rsp), %rax
	addq	48(%rsp), %rax
	addq	$96, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	eval, .-eval
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
