	.file	"memset.c"
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
	vpinsrq	$0, %r8, %xmm0, %xmm1
	vinserti128	$0x0, %xmm1, %ymm0, %ymm0
	vpinsrq	$1, %r8, %xmm0, %xmm1
	vinserti128	$0x0, %xmm1, %ymm0, %ymm0
	vextracti128	$0x1, %ymm0, %xmm1
	vpinsrq	$0, %r8, %xmm1, %xmm1
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0
	vextracti128	$0x1, %ymm0, %xmm1
	vpinsrq	$1, %r8, %xmm1, %xmm1
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0
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
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
