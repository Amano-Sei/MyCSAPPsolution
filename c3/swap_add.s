	.file	"swap_add.c"
	.text
	.globl	swap_add
	.type	swap_add, @function
swap_add:
.LFB23:
	.cfi_startproc
	movq	(%rdi), %rax
	movq	(%rsi), %rdx
	movq	%rdx, (%rdi)
	movq	%rax, (%rsi)
	addq	%rdx, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	swap_add, .-swap_add
	.globl	call
	.type	call, @function
call:
.LFB24:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	$534, 8(%rsp)
	movq	$1057, 16(%rsp)
	leaq	16(%rsp), %rsi
	leaq	8(%rsp), %rdi
	call	swap_add
	movq	8(%rsp), %rdx
	subq	16(%rsp), %rdx
	imulq	%rdx, %rax
	movq	24(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L5
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
	.size	call, .-call
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
