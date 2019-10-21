	.file	"memset.c"
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
	vinsertf128	$0x1, %xmm0, %ymm0, %ymm0
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
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
