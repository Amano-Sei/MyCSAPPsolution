	.file	"3_64.c"
	.text
	.globl	store_ele
	.type	store_ele, @function
store_ele:
.LFB23:
	.cfi_startproc
	leaq	(%rsi,%rsi,2), %rax
	leaq	(%rsi,%rax,4), %rax
	movq	%rdi, %rsi
	salq	$6, %rsi
	addq	%rsi, %rdi
	addq	%rax, %rdi
	addq	%rdi, %rdx
	leaq	A(%rip), %rax
	movq	(%rax,%rdx,8), %rax
	movq	%rax, (%rcx)
	movl	$3640, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	store_ele, .-store_ele
	.comm	A,3640,32
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
