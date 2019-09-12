	.file	"vframe.c"
	.text
	.globl	vframe
	.type	vframe, @function
vframe:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	22(,%rdi,8), %rax
	andq	$-16, %rax
	subq	%rax, %rsp
	leaq	7(%rsp), %rax
	shrq	$3, %rax
	leaq	0(,%rax,8), %r9
	movq	%r9, %r8
	leaq	-8(%rbp), %rcx
	movq	%rcx, 0(,%rax,8)
	movl	$0, %eax    ;没有compile之前一脸懵逼地看书上的代码，结果这里置0了（（（
	jmp	.L2
.L3:
	movslq	%eax, %rcx
	movq	%rdx, (%r8,%rcx,8)
	addl	$1, %eax
.L2:
	movslq	%eax, %rcx
	cmpq	%rdi, %rcx
	jl	.L3
	movq	(%r9,%rsi,8), %rax
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	vframe, .-vframe
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
