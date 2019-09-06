	.file	"comp.c"
	.text
	.globl	comp
	.type	comp, @function
comp:
.LFB23:
	.cfi_startproc
	cmpq	%rsi, %rdi
	setb	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	comp, .-comp
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
