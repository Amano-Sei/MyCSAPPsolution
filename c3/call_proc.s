	.file	"call_proc.c"
	.text
	.globl	call_proc
	.type	call_proc, @function
call_proc:
.LFB23:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	$1, 16(%rsp)
	movl	$2, 12(%rsp)
	movw	$3, 10(%rsp)
	movb	$4, 9(%rsp)
	leaq	12(%rsp), %rcx
	leaq	16(%rsp), %rsi
	leaq	9(%rsp), %rax
	pushq	%rax
	.cfi_def_cfa_offset 56
	pushq	$4
	.cfi_def_cfa_offset 64
	leaq	26(%rsp), %r9
	movl	$3, %r8d
	movl	$2, %edx
	movl	$1, %edi
	call	proc@PLT
	movslq	28(%rsp), %rax
	addq	32(%rsp), %rax
	movswl	26(%rsp), %edx
	movsbl	25(%rsp), %ecx
	subl	%ecx, %edx
	movslq	%edx, %rdx
	imulq	%rdx, %rax
	addq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	24(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L4
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	call_proc, .-call_proc
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
