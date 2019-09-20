	.file	"sum.c"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB23:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L2
.L3:
	addq	(%rdi), %rax
	addq	$8, %rdi
	subq	$1, %rsi
.L2:
	testq	%rsi, %rsi
	jne	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	sum, .-sum
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
