	.file	"tmemset.c"
	.text
	.globl	memset
	.type	memset, @function
memset:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	cmpq	$31, %rdx
	jbe	.L13
	movl	%esi, %r8d
	movzbl	%sil, %r9d
	movq	%r9, %rcx
	salq	$8, %rcx
	orq	%r9, %rcx
	movq	%rcx, %r9
	salq	$16, %r9
	orq	%r9, %rcx
	movq	%rcx, %r9
	salq	$32, %r9
	orq	%rcx, %r9
	vpinsrq	$0, %r9, %xmm0, %xmm0
	vpinsrq	$1, %r9, %xmm0, %xmm0
	vinserti128	$0x1, %xmm0, %ymm0, %ymm0
	movq	%rdi, %rcx
	jmp	.L3
.L4:
	movb	%r8b, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
.L3:
	testb	$31, %cl
	jne	.L4
	movq	%rdx, %r8
	shrq	$8, %r8
	jmp	.L5
.L6:
	vmovdqa	%ymm0, (%rcx)
	vmovdqa	%ymm0, 32(%rcx)
	vmovdqa	%ymm0, 64(%rcx)
	vmovdqa	%ymm0, 96(%rcx)
	vmovdqa	%ymm0, 128(%rcx)
	vmovdqa	%ymm0, 160(%rcx)
	vmovdqa	%ymm0, 192(%rcx)
	vmovdqa	%ymm0, 224(%rcx)
	addq	$256, %rcx
	subq	$1, %r8
.L5:
	testq	%r8, %r8
	jne	.L6
	movzbl	%dl, %r8d
	shrq	$5, %r8
	jmp	.L7
.L8:
	vmovdqa	%ymm0, (%rcx)
	addq	$32, %rcx
	subq	$1, %r8
.L7:
	testq	%r8, %r8
	jne	.L8
	movq	%rdx, %r8
	andl	$31, %r8d
	shrq	$3, %r8
	jmp	.L9
.L10:
	movq	%r9, (%rcx)
	addq	$8, %rcx
	subq	$1, %r8
.L9:
	testq	%r8, %r8
	jne	.L10
	andl	$7, %edx
	jmp	.L11
.L13:
	movq	%rdi, %rcx
	jmp	.L11
.L12:
	movb	%sil, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
.L11:
	testq	%rdx, %rdx
	jne	.L12
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
	jmp	.L15
.L17:
	addl	$1, %ebx
.L16:
	cmpl	%ebx, %r12d
	jle	.L23
	leal	0(%rbp,%rbx), %eax
	cltq
	leaq	fort(%rip), %rdx
	movzbl	(%rdx,%rax), %eax
	cmpl	%eax, %r13d
	je	.L17
	movslq	%ebx, %rax
	movsbl	(%rdx,%rax), %ecx
	movl	%ebx, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L17
.L23:
	addl	$1, %ebp
.L20:
	cmpl	$31, %ebp
	jg	.L24
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
	jmp	.L16
.L24:
	addl	$1, %r12d
.L15:
	cmpl	$2175, %r12d
	jg	.L25
	movl	$0, %ebp
	jmp	.L20
.L25:
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
