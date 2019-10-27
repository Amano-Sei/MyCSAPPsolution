	.file	"6_45.c"
	.text
	.p2align 4,,15
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB23:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leal	-3(%rdx), %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	testl	%eax, %eax
	movq	%rdi, -112(%rsp)
	movq	%rsi, 16(%rsp)
	movl	%eax, -28(%rsp)
	jle	.L13
	leal	0(,%rdx,4), %eax
	movq	%rsi, %rdi
	movslq	%edx, %r10
	movq	%r10, -88(%rsp)
	movq	%rdi, %r15
	movq	$0, -120(%rsp)
	movslq	%eax, %r14
	movq	$0, -80(%rsp)
	movl	%edx, -32(%rsp)
	leaq	(%rsi,%r14), %rax
	leal	(%rdx,%rdx), %esi
	leaq	0(,%r14,4), %r13
	movq	%rax, -48(%rsp)
	addq	%r14, %rax
	movslq	%esi, %r11
	movq	%rax, -56(%rsp)
	addq	%r14, %rax
	addl	%edx, %esi
	movq	%rax, -64(%rsp)
	leal	-4(%rdx), %eax
	movslq	%esi, %rsi
	movq	%rsi, -104(%rsp)
	movq	%r11, -96(%rsp)
	shrl	$2, %eax
	movl	%eax, %ecx
	leal	4(,%rax,4), %eax
	leaq	4(,%rcx,4), %rbx
	movl	%eax, -36(%rsp)
	movq	%rbx, -24(%rsp)
	leaq	0(,%rcx,4), %rbx
	movq	%rbx, -16(%rsp)
	movslq	%eax, %rbx
	imull	%edx, %eax
	movq	%rbx, 8(%rsp)
	cltq
	movq	%rax, (%rsp)
	leaq	16(%rdi), %rax
	movq	%rax, -8(%rsp)
	.p2align 4,,10
	.p2align 3
.L6:
	movq	-112(%rsp), %rax
	movq	-120(%rsp), %rdi
	movq	-8(%rsp), %rbx
	movq	-88(%rsp), %r8
	movq	-104(%rsp), %rcx
	movq	%r14, -72(%rsp)
	leaq	(%rax,%rdi,4), %rdx
	movq	-80(%rsp), %rdi
	movq	-16(%rsp), %rax
	addq	%rdi, %rax
	subq	%rdi, %r8
	leaq	(%rbx,%rax,4), %r12
	movq	%rdi, %rbx
	movq	-96(%rsp), %rdi
	movq	%r15, %rax
	subq	%rbx, %rcx
	subq	%rbx, %rdi
	.p2align 4,,10
	.p2align 3
.L3:
	movl	4(%rax), %ebp
	movl	8(%rax), %ebx
	movl	12(%rax), %r9d
	movl	(%rax), %r14d
	movl	%r14d, (%rdx)
	movl	%ebp, (%rdx,%r10,4)
	movl	%ebx, (%rdx,%r11,4)
	movl	%r9d, (%rdx,%rsi,4)
	movl	4(%rax,%r8,4), %ebp
	movl	8(%rax,%r8,4), %ebx
	movl	12(%rax,%r8,4), %r9d
	movl	(%rax,%r8,4), %r14d
	movl	%r14d, 4(%rdx)
	movl	%ebp, 4(%rdx,%r10,4)
	movl	%ebx, 4(%rdx,%r11,4)
	movl	%r9d, 4(%rdx,%rsi,4)
	movl	4(%rax,%rdi,4), %ebp
	movl	8(%rax,%rdi,4), %ebx
	movl	12(%rax,%rdi,4), %r9d
	movl	(%rax,%rdi,4), %r14d
	movl	%r14d, 8(%rdx)
	movl	%ebp, 8(%rdx,%r10,4)
	movl	%ebx, 8(%rdx,%r11,4)
	movl	%r9d, 8(%rdx,%rsi,4)
	movl	4(%rax,%rcx,4), %ebp
	movl	8(%rax,%rcx,4), %ebx
	movl	12(%rax,%rcx,4), %r9d
	movl	(%rax,%rcx,4), %r14d
	addq	$16, %rax
	movl	%r14d, 12(%rdx)
	movl	%ebp, 12(%rdx,%r10,4)
	movl	%ebx, 12(%rdx,%r11,4)
	movl	%r9d, 12(%rdx,%rsi,4)
	addq	%r13, %rdx
	cmpq	%rax, %r12
	jne	.L3
	movl	-32(%rsp), %r9d
	movl	-36(%rsp), %eax
	movq	-72(%rsp), %r14
	cmpl	%eax, %r9d
	jle	.L4
	movq	-120(%rsp), %rax
	addq	(%rsp), %rax
	movq	-112(%rsp), %rdi
	movq	-64(%rsp), %rbx
	movq	-56(%rsp), %rbp
	movq	-48(%rsp), %r12
	movq	%rsi, -72(%rsp)
	leaq	(%rdi,%rax,4), %rdx
	movq	8(%rsp), %rax
.L5:
	movl	(%r12,%rax,4), %r8d
	movl	0(%rbp,%rax,4), %edi
	movl	(%rbx,%rax,4), %ecx
	movl	(%r15,%rax,4), %esi
	addq	$1, %rax
	movl	%r8d, 4(%rdx)
	movl	%edi, 8(%rdx)
	movl	%esi, (%rdx)
	movl	%ecx, 12(%rdx)
	addq	%r14, %rdx
	cmpl	%eax, %r9d
	jg	.L5
	movq	-72(%rsp), %rsi
.L4:
	addq	$4, -120(%rsp)
	addq	%r14, -80(%rsp)
	addq	%r13, %r15
	movq	-120(%rsp), %rax
	addq	%r13, -48(%rsp)
	addq	%r13, -56(%rsp)
	addq	%r13, -64(%rsp)
	addq	%r14, -88(%rsp)
	addq	%r14, -96(%rsp)
	addq	%r14, -104(%rsp)
	cmpq	%rax, -24(%rsp)
	jne	.L6
	movl	-32(%rsp), %edx
.L2:
	movl	-36(%rsp), %eax
	cmpl	%eax, %edx
	jle	.L1
	movl	%eax, %ecx
	movslq	%eax, %r14
	movq	-112(%rsp), %rax
	imull	%edx, %ecx
	movq	16(%rsp), %rdi
	leal	(%rdx,%rdx), %r10d
	leal	0(,%rdx,4), %r11d
	movslq	%edx, %rbx
	leaq	(%rax,%r14,4), %rax
	movslq	%r10d, %r12
	leaq	0(,%rbx,4), %rbp
	movslq	%ecx, %rcx
	movslq	%r11d, %r11
	addl	%edx, %r10d
	movq	%rax, -104(%rsp)
	leal	-4(%rdx), %eax
	leaq	(%rdi,%rcx,4), %r9
	salq	$2, %r11
	movslq	%r10d, %r10
	shrl	$2, %eax
	movl	%eax, %esi
	leal	4(,%rax,4), %r15d
	leaq	(%rcx,%rsi,4), %rcx
	leaq	16(%rdi,%rcx,4), %r13
.L8:
	movl	-28(%rsp), %esi
	movq	-104(%rsp), %rcx
	movq	%r9, %rax
	testl	%esi, %esi
	jle	.L24
	.p2align 4,,10
	.p2align 3
.L21:
	movl	%edx, -120(%rsp)
	.p2align 4,,10
	.p2align 3
.L9:
	movl	4(%rax), %r8d
	movl	8(%rax), %edi
	addq	$16, %rax
	movl	-4(%rax), %esi
	movl	-16(%rax), %edx
	movl	%edx, (%rcx)
	movl	%r8d, (%rcx,%rbx,4)
	movl	%edi, (%rcx,%r12,4)
	movl	%esi, (%rcx,%r10,4)
	addq	%r11, %rcx
	cmpq	%rax, %r13
	jne	.L9
	movl	-120(%rsp), %edx
	cmpl	%r15d, %edx
	jle	.L8
	movl	%r15d, %ecx
.L12:
	movslq	%ecx, %rax
	movq	-112(%rsp), %rsi
	imull	%edx, %ecx
	movslq	%ecx, %rcx
	addq	%r14, %rcx
	leaq	(%rsi,%rcx,4), %rcx
	.p2align 4,,10
	.p2align 3
.L11:
	movl	(%r9,%rax,4), %esi
	addq	$1, %rax
	movl	%esi, (%rcx)
	addq	%rbp, %rcx
	cmpl	%eax, %edx
	jg	.L11
	movl	-28(%rsp), %esi
	movq	-104(%rsp), %rcx
	movq	%r9, %rax
	testl	%esi, %esi
	jg	.L21
.L24:
	xorl	%ecx, %ecx
	jmp	.L12
.L1:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	movl	$0, -36(%rsp)
	jmp	.L2
	.cfi_endproc
.LFE23:
	.size	transpose, .-transpose
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
