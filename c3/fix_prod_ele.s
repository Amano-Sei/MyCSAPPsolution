	.file	"fix_prod_ele.c"
	.text
	.globl	fix_prod_ele
	.type	fix_prod_ele, @function
fix_prod_ele:
.LFB23:
	.cfi_startproc
	salq	$6, %rdx                ;i = i*16*4
	addq	%rdx, %rdi              ;%rdi = (ul)A + i
	leaq	(%rsi,%rcx,4), %rdx     ;%rdx = (ul)B + 4*k
	leaq	1024(%rdx), %rsi        ;4+4+2=10 %rsi = &B[N][k]
	movl	$0, %eax                ;result = 0
.L2:
	movl	(%rdi), %ecx
	imull	(%rdx), %ecx
	addl	%ecx, %eax
	addq	$4, %rdi
	addq	$64, %rdx               ;4+2=6
	cmpq	%rsi, %rdx
	jne	.L2
	rep ret
	.cfi_endproc
.LFE23:
	.size	fix_prod_ele, .-fix_prod_ele
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
