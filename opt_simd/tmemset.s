	.file	"tmemset.c"
	.text
	.globl	memset
	.type	memset, @function
memset:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	cmpq	$1023, %rdx
	ja	.L9
	movq	%rdi, %rcx
	jmp	.L3
.L4:
	movb	%sil, (%rcx)
	leaq	1(%rcx), %rcx
.L2:
	testb	$31, %cl
	jne	.L4
	movzbl	%sil, %r9d
	movq	%r9, %r8
	salq	$56, %r8
	movq	%r9, %rdi
	salq	$48, %rdi
	orq	%rdi, %r8
	movq	%r9, %rdi
	salq	$40, %rdi
	movq	%r9, %r10
	salq	$32, %r10
	orq	%r10, %rdi
	orq	%rdi, %r8
	movq	%r9, %rdi
	salq	$24, %rdi
	movq	%r9, %r10
	salq	$16, %r10
	orq	%r10, %rdi
	movq	%r9, %r10
	salq	$8, %r10
	orq	%r10, %r9
	orq	%rdi, %r9
	orq	%r9, %r8
	vpxor	%xmm0, %xmm0, %xmm0
	vpinsrq	$0, %r8, %xmm0, %xmm0
	vpinsrq	$1, %r8, %xmm0, %xmm0
	vinserti128	$0x0, %xmm0, %ymm0, %ymm0
	vinserti128	$0x1, %xmm0, %ymm0, %ymm0
	jmp	.L5
.L9:
	movq	%rdi, %rcx
	jmp	.L2
.L6:
	vmovdqa	%ymm0, (%rcx)
	addq	$32, %rcx
	subq	$32, %rdx
.L5:
	cmpq	$31, %rdx
	ja	.L6
	jmp	.L3
.L8:
	movb	%sil, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
.L3:
	testq	%rdx, %rdx
	jne	.L8
	rep ret
	.cfi_endproc
.LFE23:
	.size	memset, .-memset
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"warning...with %d %d\n"
.LC1:
	.string	"done..."
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
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
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movl	$1920, %r12d
	jmp	.L11
.L13:
	addl	$1, %ebx
.L12:
	cmpl	%ebx, %r12d
	jle	.L19
	leal	0(%rbp,%rbx), %eax
	cltq
	leaq	fort(%rip), %rdx
	movzbl	(%rdx,%rax), %eax
	cmpl	%eax, %r13d
	je	.L13
	movslq	%ebx, %rax
	movsbl	(%rdx,%rax), %ecx
	movl	%ebx, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L13
.L19:
	addl	$1, %ebp
.L16:
	cmpl	$31, %ebp
	jg	.L20
	leal	-1920(%r12,%rbp), %esi
	movl	%esi, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %esi
	movzbl	%sil, %esi
	subl	%eax, %esi
	movl	%esi, %r13d
	movslq	%ebp, %rdi
	leaq	fort(%rip), %rax
	addq	%rax, %rdi
	movslq	%r12d, %rdx
	call	memset
	movl	$0, %ebx
	jmp	.L12
.L20:
	addl	$1, %r12d
.L11:
	cmpl	$2175, %r12d
	jg	.L21
	movl	$0, %ebp
	jmp	.L16
.L21:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	addq	$8, %rsp
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
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.comm	fort,3000,32
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
