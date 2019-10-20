	.file	"5_14.c"
	.text
	.globl	new_vec
	.type	new_vec, @function
new_vec:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbp
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L1
	movq	%rbp, (%rax)
	movq	%rbp, 16(%rax)
	testq	%rbp, %rbp
	jg	.L6
	movl	$0, %eax
.L3:
	movq	%rax, 8(%rbx)
.L1:
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	movl	$8, %esi
	movq	%rbp, %rdi
	call	calloc@PLT
	testq	%rax, %rax
	jne	.L3
	movq	%rbx, %rdi
	call	free@PLT
	movl	$0, %ebx
	jmp	.L1
	.cfi_endproc
.LFE41:
	.size	new_vec, .-new_vec
	.globl	free_vec
	.type	free_vec, @function
free_vec:
.LFB42:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L8
	call	free@PLT
.L8:
	movq	%rbx, %rdi
	call	free@PLT
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE42:
	.size	free_vec, .-free_vec
	.globl	get_vec_element
	.type	get_vec_element, @function
get_vec_element:
.LFB43:
	.cfi_startproc
	testq	%rsi, %rsi
	js	.L12
	cmpq	%rsi, (%rdi)
	jle	.L13
	movq	8(%rdi), %rax
	movsd	(%rax,%rsi,8), %xmm0
	movsd	%xmm0, (%rdx)
	movl	$1, %eax
	ret
.L12:
	movl	$0, %eax
	ret
.L13:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE43:
	.size	get_vec_element, .-get_vec_element
	.globl	vec_length
	.type	vec_length, @function
vec_length:
.LFB44:
	.cfi_startproc
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE44:
	.size	vec_length, .-vec_length
	.globl	get_vec_start
	.type	get_vec_start, @function
get_vec_start:
.LFB45:
	.cfi_startproc
	movq	8(%rdi), %rax
	ret
	.cfi_endproc
.LFE45:
	.size	get_vec_start, .-get_vec_start
	.globl	set_vec_element
	.type	set_vec_element, @function
set_vec_element:
.LFB46:
	.cfi_startproc
	testq	%rsi, %rsi
	js	.L18
	cmpq	%rsi, (%rdi)
	jle	.L19
	salq	$3, %rsi
	addq	8(%rdi), %rsi
	movsd	%xmm0, (%rsi)
	movl	$1, %eax
	ret
.L18:
	movl	$0, %eax
	ret
.L19:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE46:
	.size	set_vec_element, .-set_vec_element
	.globl	set_vec_length
	.type	set_vec_length, @function
set_vec_length:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbx
	movq	%rsi, %rbp
	cmpq	%rsi, 16(%rdi)
	jl	.L23
.L21:
	movq	%rbp, (%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore_state
	movq	8(%rdi), %rdi
	call	free@PLT
	movl	$8, %esi
	movq	%rbp, %rdi
	call	calloc@PLT
	movq	%rax, 8(%rbx)
	movq	%rbp, 16(%rbx)
	jmp	.L21
	.cfi_endproc
.LFE47:
	.size	set_vec_length, .-set_vec_length
	.globl	inner4
	.type	inner4, @function
inner4:
.LFB48:
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
	movq	%rdi, %rbx
	movq	%rsi, %r13
	movq	%rdx, %r12
	call	vec_length
	movq	%rax, %rbp
	movq	%rbx, %rdi
	call	get_vec_start
	movq	%rax, %rbx
	movq	%r13, %rdi
	call	get_vec_start
	pxor	%xmm0, %xmm0
	movl	$0, %edx
	jmp	.L25
.L26:
	movsd	(%rax,%rdx,8), %xmm1
	mulsd	(%rbx,%rdx,8), %xmm1
	addsd	%xmm0, %xmm1
	leaq	1(%rdx), %rcx
	movsd	(%rax,%rcx,8), %xmm0
	mulsd	(%rbx,%rcx,8), %xmm0
	addsd	%xmm1, %xmm0
	leaq	2(%rdx), %rcx
	movsd	(%rax,%rcx,8), %xmm1
	mulsd	(%rbx,%rcx,8), %xmm1
	addsd	%xmm1, %xmm0
	leaq	3(%rdx), %rcx
	movsd	(%rax,%rcx,8), %xmm1
	mulsd	(%rbx,%rcx,8), %xmm1
	addsd	%xmm0, %xmm1
	leaq	4(%rdx), %rcx
	movsd	(%rax,%rcx,8), %xmm0
	mulsd	(%rbx,%rcx,8), %xmm0
	addsd	%xmm0, %xmm1
	leaq	5(%rdx), %rcx
	movsd	(%rax,%rcx,8), %xmm0
	mulsd	(%rbx,%rcx,8), %xmm0
	addsd	%xmm1, %xmm0
	addq	$6, %rdx
.L25:
	leaq	-5(%rbp), %rcx
	cmpq	%rdx, %rcx
	jg	.L26
	jmp	.L27
.L28:
	movsd	(%rax,%rdx,8), %xmm1
	mulsd	(%rbx,%rdx,8), %xmm1
	addsd	%xmm1, %xmm0
	addq	$1, %rdx
.L27:
	cmpq	%rbp, %rdx
	jl	.L28
	movsd	%xmm0, (%r12)
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE48:
	.size	inner4, .-inner4
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
