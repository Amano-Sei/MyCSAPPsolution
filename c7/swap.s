	.file	"swap.c"
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB0:
	.cfi_startproc
	leaq	4+buf(%rip), %rax
	movq	%rax, bufp1(%rip)
	movq	bufp0(%rip), %rax
	movl	(%rax), %edx
	movl	4+buf(%rip), %ecx
	movl	%ecx, (%rax)
	movq	bufp1(%rip), %rax
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE0:
	.size	swap, .-swap
	.comm	bufp1,8,8
	.globl	bufp0
	.section	.data.rel,"aw",@progbits
	.align 8
	.type	bufp0, @object
	.size	bufp0, 8
bufp0:
	.quad	buf
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
