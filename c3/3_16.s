	.file	"3_16.c"
	.text
	.globl	cond
	.type	cond, @function
cond:
.LFB23:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L1
	cmpq	%rdi, (%rsi)
	jge	.L1
	movq	%rdi, (%rsi)
.L2:
.L1:
	rep ret
	.cfi_endproc
.LFE23:
	.size	cond, .-cond
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
