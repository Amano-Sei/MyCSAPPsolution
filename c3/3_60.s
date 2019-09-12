	.file	"3_60.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB23:
	.cfi_startproc
	movl	%esi, %ecx
	movl	$1, %edx
	movl	$0, %eax
	jmp	.L2
.L3:
	movq	%rdx, %r8
	andq	%rdi, %r8
	orq	%r8, %rax
	salq	%cl, %rdx
.L2:
	testq	%rdx, %rdx
	jne	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	loop, .-loop
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
