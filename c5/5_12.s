	.file	"5_12.c"
	.text
	.globl	psum1
	.type	psum1, @function
psum1:
.LFB23:
	.cfi_startproc
	pxor	%xmm0, %xmm0
	movl	$0, %eax
	jmp	.L2
.L3:
	addss	(%rdi,%rax,4), %xmm0
	movss	%xmm0, (%rsi,%rax,4)
	addq	$1, %rax
.L2:
	cmpq	%rdx, %rax
	jl	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	psum1, .-psum1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
