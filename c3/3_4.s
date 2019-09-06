	.file	"3_4.c"
	.text
	.globl	exchange
	.type	exchange, @function
exchange:
.LFB23:
	.cfi_startproc
	movzbl	(%rdi), %eax
	movq	%rax, (%rsi)
	ret
	.cfi_endproc
.LFE23:
	.size	exchange, .-exchange
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
