	.file	"combine3.c"
	.text
	.p2align 4,,15
	.globl	combine3
	.type	combine3, @function
combine3:
.LFB23:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbx
	call	vec_length@PLT
	movq	%rbp, %rdi
	movq	%rax, %r12
	call	get_vec_start@PLT
	movsd	.LC0(%rip), %xmm0
	testq	%r12, %r12
	movsd	%xmm0, (%rbx)
	jle	.L1
	leaq	(%rax,%r12,8), %rdx
	.p2align 4,,10
	.p2align 3
.L3:
	mulsd	(%rax), %xmm0
	addq	$8, %rax
	cmpq	%rdx, %rax
	movsd	%xmm0, (%rbx)
	jne	.L3
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	combine3, .-combine3
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
