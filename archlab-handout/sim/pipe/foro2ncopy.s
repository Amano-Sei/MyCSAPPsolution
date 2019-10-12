	.file	"foro2ncopy.c"
	.text
	.p2align 4,,15
	.globl	ncopy
	.type	ncopy, @function
ncopy:
.LFB11:
	.cfi_startproc
	testq	%rdx, %rdx
	jle	.L5
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movq	(%rdi,%rcx,8), %r8
	testq	%r8, %r8
	movq	%r8, (%rsi,%rcx,8)
	setg	%r8b
	addq	$1, %rcx
	movzbl	%r8b, %r8d
	addq	%r8, %rax
	cmpq	%rdx, %rcx
	jne	.L4
	rep ret
.L5:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	ncopy, .-ncopy
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
