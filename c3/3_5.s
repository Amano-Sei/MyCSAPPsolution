	.file	"3_5.c"
	.text
	.globl	decode1
	.type	decode1, @function
decode1:
.LFB23:
	.cfi_startproc
	movq	(%rdi), %r8
	movq	(%rsi), %rcx
	movq	(%rdx), %rax
	movq	%r8, (%rsi)
	movq	%rcx, (%rdx)
	movq	%rax, (%rdi)
	ret
	.cfi_endproc
.LFE23:
	.size	decode1, .-decode1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
