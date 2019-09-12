	.file	"tstruct.c"
	.text
	.globl	t1
	.type	t1, @function
t1:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	movq	-40(%rsp), %rsi
	movq	-32(%rsp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-24(%rsp), %rdx
	movq	%rdx, 16(%rax)
	ret
	.cfi_endproc
.LFE23:
	.size	t1, .-t1
	.globl	t2
	.type	t2, @function
t2:
.LFB24:
	.cfi_startproc
	movq	%rdi, %rax
	movq	-40(%rsp), %rsi
	movq	-32(%rsp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-24(%rsp), %rdx
	movq	%rdx, 16(%rax)
	ret
	.cfi_endproc
.LFE24:
	.size	t2, .-t2
	.globl	t3
	.type	t3, @function
t3:
.LFB25:
	.cfi_startproc
	movq	%rdi, %rax
	movslq	%esi, %rsi
	movq	%rsi, -40(%rsp)
	movslq	%edx, %rdx
	movq	%rdx, -32(%rsp)
	movq	-40(%rsp), %rsi
	movq	-32(%rsp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-24(%rsp), %rdx
	movq	%rdx, 16(%rax)
	ret
	.cfi_endproc
.LFE25:
	.size	t3, .-t3
	.globl	t4
	.type	t4, @function
t4:
.LFB26:
	.cfi_startproc
	movq	%rdi, %rax
	addl	%edx, %esi
	addl	%esi, %ecx
	addl	%r8d, %ecx
	leal	(%rcx,%r9), %edx
	addl	8(%rsp), %edx
	addl	16(%rsp), %edx
	movslq	%edx, %rdx
	addq	24(%rsp), %rdx
	movq	%rdx, -40(%rsp)
	movq	-40(%rsp), %rsi
	movq	-32(%rsp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-24(%rsp), %rdx
	movq	%rdx, 16(%rax)
	ret
	.cfi_endproc
.LFE26:
	.size	t4, .-t4
	.globl	t5
	.type	t5, @function
t5:
.LFB27:
	.cfi_startproc
	movq	%rdi, %rax
	addl	%edx, %esi
	addl	%esi, %ecx
	addl	%r8d, %ecx
	leal	(%rcx,%r9), %edx
	addl	32(%rsp), %edx
	addl	40(%rsp), %edx
	movslq	%edx, %rdx
	addq	8(%rsp), %rdx
	movq	%rdx, -40(%rsp)
	movq	-40(%rsp), %rsi
	movq	-32(%rsp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-24(%rsp), %rdx
	movq	%rdx, 16(%rax)
	ret
	.cfi_endproc
.LFE27:
	.size	t5, .-t5
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
