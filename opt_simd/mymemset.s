	.file	"mymemset.cpp"
	.text
	.globl	_Z8mymemsetPvim
	.type	_Z8mymemsetPvim, @function
_Z8mymemsetPvim:
.LFB30:
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
.L4:
	testb	$31, %cl
	je	.L3
	movb	%r8b, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
	jmp	.L4
.L3:
	movq	%rdx, %r8
	shrq	$8, %r8
.L6:
	testq	%r8, %r8
	je	.L5
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
	jmp	.L6
.L5:
	movzbl	%dl, %r8d
	shrq	$5, %r8
.L8:
	testq	%r8, %r8
	je	.L7
	vmovdqa	%ymm0, (%rcx)
	addq	$32, %rcx
	subq	$1, %r8
	jmp	.L8
.L7:
	movq	%rdx, %r8
	andl	$31, %r8d
	shrq	$3, %r8
.L10:
	testq	%r8, %r8
	je	.L9
	movq	%r9, (%rcx)
	addq	$8, %rcx
	subq	$1, %r8
	jmp	.L10
.L9:
	andl	$7, %edx
.L12:
	testq	%rdx, %rdx
	je	.L11
	movb	%sil, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
	jmp	.L12
.L13:
	movq	%rdi, %rcx
	jmp	.L12
.L11:
	rep ret
	.cfi_endproc
.LFE30:
	.size	_Z8mymemsetPvim, .-_Z8mymemsetPvim
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
