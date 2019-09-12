	.file	"3_58.c"
	.text
	.globl	decode2
	.type	decode2, @function
decode2:
.LFB23:
	.cfi_startproc
	subq	%rdx, %rsi
	movq	%rsi, %rax
	salq	$63, %rax
	sarq	$63, %rax
	imulq	%rdi, %rsi
	xorq	%rsi, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	decode2, .-decode2
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
