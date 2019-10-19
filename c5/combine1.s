	.file	"combine1.c"
	.text
	.globl	combine1
	.type	combine1, @function
combine1:
.LFB23:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movq	%rdi, %r12
	movq	%rsi, %rbp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	$1, (%rsi)
	movl	$0, %ebx
	movq	%rsp, %r13
	jmp	.L2
.L3:
	movq	%r13, %rdx
	movq	%rbx, %rsi
	movq	%r12, %rdi
	call	get_vec_element@PLT
	movq	0(%rbp), %rax
	imulq	(%rsp), %rax
	movq	%rax, 0(%rbp)
	addq	$1, %rbx
.L2:
	movq	%r12, %rdi
	call	vec_length@PLT
	cmpq	%rbx, %rax
	jg	.L3
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L6
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	combine1, .-combine1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
