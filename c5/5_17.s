	.file	"5_17.c"
	.text
	.globl	mymemset
	.type	mymemset, @function
mymemset:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	movzbl	%sil, %r9d
	movq	%r9, %r8
	movl	$1, %ecx
	jmp	.L2
.L3:
	salq	$8, %r8
	orq	%r9, %r8
	addl	$1, %ecx
.L2:
	cmpl	$7, %ecx
	jbe	.L3
	movq	%rax, %rcx
	jmp	.L4
.L6:
	movb	%sil, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
.L4:
	testb	$7, %cl
	je	.L7
	testq	%rdx, %rdx
	jne	.L6
	jmp	.L7
.L8:
	movq	%r8, (%rcx)
	addq	$8, %rcx
	subq	$8, %rdx
.L7:
	cmpq	$7, %rdx
	ja	.L8
	jmp	.L9
.L10:
	movb	%sil, (%rcx)
	subq	$1, %rdx
	leaq	1(%rcx), %rcx
.L9:
	testq	%rdx, %rdx
	jne	.L10
	rep ret
	.cfi_endproc
.LFE23:
	.size	mymemset, .-mymemset
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
