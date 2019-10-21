	.file	"pp3.c"
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
	vmovsd	(%rax,%rsi,8), %xmm0
	vmovsd	%xmm0, (%rdx)
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
	vmovsd	%xmm0, (%rsi)
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
	.globl	inner8
	.type	inner8, @function
inner8:
.LFB48:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x68,0x6
	.cfi_escape 0x10,0xd,0x2,0x76,0x78
	.cfi_escape 0x10,0xc,0x2,0x76,0x70
	pushq	%rbx
	subq	$80, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x60
	movq	%rdi, %rbx
	movq	%rsi, %r13
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	call	vec_length
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	get_vec_start
	movq	%rax, %rbx
	movq	%r13, %rdi
	call	get_vec_start
	vxorpd	%xmm0, %xmm0, %xmm0
	jmp	.L25
.L27:
	vmovsd	(%rax), %xmm1
	vmulsd	(%rbx), %xmm1, %xmm1
	vaddsd	%xmm1, %xmm0, %xmm0
	subq	$1, %r12
	leaq	8(%rax), %rax
	leaq	8(%rbx), %rbx
.L25:
	testb	$31, %bl
	je	.L26
	testq	%r12, %r12
	jg	.L27
.L26:
	vxorpd	%xmm1, %xmm1, %xmm1
	vmovapd	%ymm1, -112(%rbp)
	jmp	.L28
.L29:
	vmovapd	(%rax), %ymm1
	vmulpd	(%rbx), %ymm1, %ymm1
	vaddpd	-112(%rbp), %ymm1, %ymm1
	vmovapd	%ymm1, -112(%rbp)
	addq	$32, %rbx
	addq	$32, %rax
	subq	$4, %r12
.L28:
	cmpq	$3, %r12
	ja	.L29
	jmp	.L30
.L31:
	vmovsd	(%rax), %xmm1
	vmulsd	(%rbx), %xmm1, %xmm1
	vaddsd	%xmm1, %xmm0, %xmm0
	subq	$1, %r12
	leaq	8(%rax), %rax
	leaq	8(%rbx), %rbx
.L30:
	testq	%r12, %r12
	jg	.L31
	movl	$0, %eax
	jmp	.L32
.L33:
	movslq	%eax, %rdx
	vaddsd	-112(%rbp,%rdx,8), %xmm0, %xmm0
	addl	$1, %eax
.L32:
	cmpl	$3, %eax
	jbe	.L33
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L36
	addq	$80, %rsp
	popq	%rbx
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%r12
	popq	%r13
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
.L36:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE48:
	.size	inner8, .-inner8
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
