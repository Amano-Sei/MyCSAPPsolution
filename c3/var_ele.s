	.file	"var_ele.c"
	.text
	.globl	var_ele
	.type	var_ele, @function
var_ele:
.LFB0:
	.cfi_startproc
	imulq	%rdi, %rdx
	leaq	(%rsi,%rdx,4), %rax
	movl	(%rax,%rcx,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	var_ele, .-var_ele
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	subq	$424, %rsp
	.cfi_def_cfa_offset 432
	movq	%fs:40, %rax
	movq	%rax, 408(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	movl	$50, %ecx
	rep stosq
	movl	$1, (%rsp)
	movq	%rsp, %rsi
	movl	$0, %edx
	movl	$1, %edi
	call	var_ele
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	408(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L5
	movl	$0, %eax
	addq	$424, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
